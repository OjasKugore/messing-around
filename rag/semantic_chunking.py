
###USE RECURSIVE FOR STRUCTURED DOCUMENTS WITH HEADERS AND CLEAR TOPIC DEMARCATION
###USE SEMANTIC FOR JUMBLED TEXT WHERE DATA SHIFTS WITHIN SAME PARAGRAPH



from langchain_text_splitters import RecursiveCharacterTextSplitter
from langchain_experimental.text_splitter import SemanticChunker
from langchain_google_genai import GoogleGenerativeAIEmbeddings
from langchain_chroma import Chroma
import os 
from dotenv import load_dotenv

load_dotenv()

embeddings = GoogleGenerativeAIEmbeddings(model="models/gemini-embedding-001")

# Multi-topic sample document to test semantic chunking boundary detection
sample_text = """
Space exploration has advanced rapidly over the past few decades. Scientists and space agencies like NASA and ESA are actively planning human missions to Mars with the goal of establishing permanent human settlements. Key engineering challenges include long-duration radiation shielding, closed-loop life support systems, and in-situ resource utilization—such as harvesting subsurface ice to produce oxygen and rocket propellant. Furthermore, autonomous rovers like Perseverance are analyzing rock samples to search for ancient biosignatures, while satellite constellations continuously map Martian topography and atmospheric dynamics.

On a completely different note, authentic Neapolitan pizza represents centuries of Italian culinary heritage governed by strict traditional guidelines. True pizza Napoletana relies on Type 0 or 00 wheat flour, natural yeast, sea salt, and mineral water. The dough undergoes a slow fermentation process lasting 8 to 24 hours to develop its signature airy crust, known as the cornicione. Hand-crushed San Marzano tomatoes grown on the volcanic slopes of Mount Vesuvius and fresh mozzarella di bufala are carefully distributed across the stretched dough. The pizza is then flash-baked in a domed wood-fired oven at temperatures reaching 900 degrees Fahrenheit for no more than 60 to 90 seconds.

Switching to modern technology, artificial intelligence and deep neural networks have fundamentally transformed modern computing. Deep learning models consist of interconnected node layers that extract hierarchical features from raw data. During training, optimization algorithms like gradient descent adjust millions or billions of parameters via backpropagation. Convolutional neural networks dominate visual perception tasks like medical imaging and autonomous driving, whereas transformer architectures power state-of-the-art large language models, enabling natural conversation, code generation, and complex reasoning across multilingual corpora.

Meanwhile, marine ecosystems like coral reefs support over 25 percent of all ocean marine life despite covering less than one percent of the ocean floor. Coral reefs are living biogenic structures constructed by colonies of tiny cnidarian polyps that secrete calcium carbonate skeletons over thousands of years. These fragile underwater rainforests provide essential habitats for fish, protect coastal shores from wave erosion, and support global fisheries. However, anthropogenic climate change, rising sea surface temperatures, and ocean acidification pose severe threats, causing widespread coral bleaching and marine biodiversity loss.

Lastly, the monuments of Ancient Egypt stand as wonders of ancient civil engineering and architectural mastery. The Great Pyramid of Giza, constructed during the reign of Pharaoh Khufu in the 26th century BCE, was built using over two million limestone and granite blocks. Ancient Egyptian builders achieved remarkable astronomical alignment, orienting the pyramid's base almost perfectly to true north. Elaborate tomb complexes, subterranean burial chambers, and intricate hieroglyphic inscriptions offer invaluable insights into ancient Egyptian religious beliefs regarding the afterlife, mummification rituals, and divine kingship.
"""

##using recursive
recursive_splitter = RecursiveCharacterTextSplitter(
    chunk_size = 400,
    chunk_overlap = 50,
    separators=["\n\n", "\n", ",", ""]
)

recursive_chunks = recursive_splitter.split_text(sample_text)

for i, chunk in enumerate(recursive_chunks):
    print(f"=========CHUNK {i+1}=============")
    print(chunk[:100] + '...' if len(chunk) > 100 else chunk)

##semantic chunking
semantic_splitter = SemanticChunker(
    embeddings,
    breakpoint_threshold_type='percentile',
    breakpoint_threshold_amount=80 #if cosine distance(1-costheta) is less than the 90th percentile mark it splits
)

semantic_chunks = semantic_splitter.split_text(sample_text)

print("==============SEMANTIC CHUNKING=================")

for i, chunk in enumerate(semantic_chunks):
    print(f"=========CHUNK {i+1}=============")
    print(chunk[:100] + '...' if len(chunk) > 100 else chunk)


r_vectorstore = Chroma.from_texts(
    recursive_chunks,
    embeddings,
    collection_name="recursive_chunks" 
)

s_vectorstore = Chroma.from_texts(
    semantic_chunks,
    embeddings,
    collection_name="semantic_chunks"
)

test_queries = [
    "Who are planning space missions to mars?",
    "How to make neapolitan pizza?",
    "What are deep learning models?",
    "what are the dangers faced by coral reefs?",
    "when was the giza pyramid constructed?"
]

def test_retrieval(query, vectorstore, name):
    results = vectorstore.similarity_search(query, k=1)
    print(f"\n{name} - Query: \"{query}\"")
    if results:
        print(f"Retrieved: {results[0].page_content[:150]}...")
        return results[0].page_content
    return "No result"


for query in test_queries:
    print(f"\n==================== Q: '{query}' ====================")
    test_retrieval(query, r_vectorstore, 'RECURSIVE')
    test_retrieval(query, s_vectorstore, 'SEMANTIC')
