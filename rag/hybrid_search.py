from langchain_chroma import Chroma
from langchain_google_genai import GoogleGenerativeAIEmbeddings
from langchain_community.retrievers import BM25Retriever
from langchain_core.documents import Document
from langchain_classic.retrievers import EnsembleRetriever

from dotenv import load_dotenv

load_dotenv()

embeddings  = GoogleGenerativeAIEmbeddings(model="models/gemini-embedding-001")

documents = [
    Document(
        page_content=(
            "Product SKU-7742X is our flagship router. It supports "
            "gigabit speeds and advanced QoS features."
        ),
        metadata={"type": "product"},
    ),
    Document(
        page_content=(
            "For network connectivity issues, first check the "
            "ethernet cable and router status lights."
        ),
        metadata={"type": "troubleshooting"},
    ),
    Document(
        page_content=(
            "Error code E_CONN_REFUSED indicates the server "
            "rejected the connection. Check firewall settings."
        ),
        metadata={"type": "error"},
    ),
    Document(
        page_content=(
            "To reset your router, press and hold the pinhole reset button "
            "on the back for 10 seconds until all LEDs flash."
        ),
        metadata={"type": "troubleshooting"},
    ),
    Document(
        page_content=(
            "Product SKU-9900Y features dual-band Wi-Fi 6 with mesh network capability."
        ),
        metadata={"type": "product"},
    ),
]

print(f"Loaded {len(documents)} documents")


vectorstore = Chroma.from_documents(
    documents, embeddings, collection_name="hybrid_test"
)

vector_retriever = vectorstore.as_retriever(
    search_kwargs = {'k' : 3}
)

print('Vector retriever ready.')

bm25retriever = BM25Retriever.from_documents(
    documents, k=3
)

print("BM25 retriever ready.")

ensemble = EnsembleRetriever(
    retrievers=[vector_retriever, bm25retriever],
    weights=[0.5, 0.5]
)

print("Hybrid retriever ready.")

def test_query(query, name ,retriever):
    '''Test a query and show results'''
    results = retriever.invoke(query)
    print(f"\n{name} - Query: \"{query}\"")
    for i, doc in enumerate(results):
        preview = doc.page_content[:80] + '...'
        print(f"    {i+1}. {preview}")
    return results

test_queries = [
    "E_CONN_REFUSED",  #for BM25
    "How do I fix my internet connection?",  # Vector
    "SKU-7742X flagship router",  # Product keyword match
    "router reset button instructions",  # Mixed semantic & keyword query
]

if __name__ == "__main__":
    for q in test_queries:
        print(f"\n==================== Query: '{q}' ====================")
        test_query(q, "Vector Retriever", vector_retriever)
        test_query(q, "BM25 Retriever", bm25retriever)
        test_query(q, "Ensemble (Hybrid) Retriever", ensemble)