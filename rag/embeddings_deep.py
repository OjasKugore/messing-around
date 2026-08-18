from langchain_google_genai import GoogleGenerativeAIEmbeddings
from dotenv import load_dotenv
from numpy.linalg import norm
import numpy as np
load_dotenv()

embeddings = GoogleGenerativeAIEmbeddings(model = "gemini-embedding-2-preview")

def basic_embeddings():


    text = "What is machine learning?"
    single_embedding = embeddings.embed_query(text)
    print(f"Vector dimensions: {len(single_embedding)}")
    print(f"First 5 values: {single_embedding[:5]}")
    print(f"Vector norm: {norm(single_embedding): .4f}") 

def batch_embeddings():
    text = [ ##for multiple docs
        "what is machine learning?",
        "explain the conept of overfitting in ML.",
        "how does a neural network work?"
    ]

    batch_embeddings =embeddings.embed_documents(text)
    for i, emb in enumerate(batch_embeddings):
        print(f"Text {i+1} Dimensions: {len(emb)}")
        print(f"Text {i+1} First 5 values: {emb[:5]}")
        print(f"Text {i+1} Norm: {norm(emb)}")

def similarity_search():
    docs = [
        "python is a programming language.",
        "javascript is used for web development.",
        "machine learning enables ai applications",
        "deep learning uses neural networks",
        "cats are popular pets"
    ]

    query = "What programming languages exist?"

    #embed docs and query
    docs_embed = embeddings.embed_documents(docs)
    query_embed = embeddings.embed_query(query)

    #compute cosine similarity
    def cosine_similarity(vec1, vec2):
        return np.dot(vec1, vec2) / (norm(vec1) * norm(vec2))

    similarities = [cosine_similarity(doc_emb, query_embed) for doc_emb in docs_embed]
    joined = zip(docs, similarities)
    results = sorted(joined, key=lambda x: x[1], reverse=True)

    print(f"Query: {query}")
    for doc, score in results:
        print(f"Doc: {doc}")
        print(f"Similarity Score: {score}")
        print("-----------")


if __name__ == "__main__":
    similarity_search()