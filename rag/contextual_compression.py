##llm, retriever
from langchain_google_genai import ChatGoogleGenerativeAI
from langchain_google_genai import GoogleGenerativeAI
from langchain_chroma import Chroma
from langchain_classic.retrievers import ContextualCompressionRetriever
from langchain_google_genai import GoogleGenerativeAIEmbeddings
from langchain_classic.retrievers.document_compressors import LLMChainExtractor
from langchain_text_splitters import RecursiveCharacterTextSplitter
from dotenv import load_dotenv
load_dotenv()

sample_text = """
LangChain is an open-source development framework designed to streamline the lifecycle of applications powered by large language models (LLMs). It provides comprehensive abstractions for prompt management, document loaders, text splitters, vector stores, and execution chains. Developers frequently leverage LangChain in Python or TypeScript to build Retrieval-Augmented Generation (RAG) pipelines, conversational agents, and data analysis assistants. On a side note, the average distance from Earth to the Moon is approximately 384,400 kilometers, and lunar eclipses occur when the Earth moves directly between the Sun and the Moon, casting a shadow across the lunar surface.

LangGraph is a specialized extension library built on top of LangChain for constructing stateful, multi-agent LLM workflows. By representing agent interactions as directed graphs with explicit nodes and edges, LangGraph allows engineers to build cyclical execution loops, persistent session memory, human-in-the-loop approvals, and fault-tolerant state recovery. Meanwhile, the Amazon rainforest produces roughly 20 percent of the planet's atmospheric oxygen, spanning over 5.5 million square kilometers across nine South American nations, supporting an immense ecosystem of flora and fauna.

LlamaIndex (formerly GPT Index) is a data framework tailored specifically for LLM applications that ingest, index, and query private or domain-specific data structures. It offers specialized data connectors, advanced RAG index structures, and query engines capable of synthesizing responses across structured SQL databases and unstructured document repositories. In contrast, espresso coffee is brewed by forcing near-boiling water under high pressure through finely ground coffee beans, resulting in a thick, concentrated beverage topped with a characteristic reddish-brown foam known as crema.

Semantic Chunking is an advanced document processing technique that splits text based on semantic meaning rather than arbitrary character counts. By analyzing sentence embeddings and calculating cosine distance thresholds between adjacent sentences, semantic splitters group related concepts together into coherent chunks. On another topic, the Great Wall of China is an ancient series of fortifications built across the historical northern borders of ancient Chinese states, stretching over 21,000 kilometers in total length across mountains and deserts.

Hybrid Search combines dense vector retrieval with sparse keyword search (such as BM25) using Reciprocal Rank Fusion (RRF) to maximize search precision. Vector search excels at capturing semantic intent and fuzzy conceptual similarity, whereas BM25 accurately matches exact product codes, acronyms, and unique proper nouns. Furthermore, honey bees perform a complex figure-eight movement known as the waggle dance to communicate the direction and distance of nectar sources to other hive members.
"""
embeddings = GoogleGenerativeAIEmbeddings(model="gemini-embedding-2-preview")

splitter = RecursiveCharacterTextSplitter(
    chunk_size = 600,
    chunk_overlap = 50,
    separators=["\n\n", "\n", " ", ""]
)

chunks = splitter.split_text(sample_text)

vector_database = Chroma.from_texts(
    texts=chunks,
    embedding=embeddings
)

llm = ChatGoogleGenerativeAI(model="gemini-3.5-flash-lite")
compressor = LLMChainExtractor.from_llm(llm)

contextual_compressor = ContextualCompressionRetriever(
    base_compressor=compressor,
    base_retriever=vector_database.as_retriever(search_kwargs={"k": 2})
)

query = "how long is the great wall?"

#without contextual compression
result = vector_database.as_retriever(search_kwargs={"k":2}).invoke(query)
print("========WITHOUT CONTEXTUAL COMPRESSION==========")
print(f"Query: {query}")
print(f"Answer: {result[0].page_content}")

#with contextual compression
result1 = contextual_compressor.invoke(query)
print("===========WITH COMPRESSION=============")
print(f"Query: {query}")
print(f"Answer: {result1[0].page_content}")

