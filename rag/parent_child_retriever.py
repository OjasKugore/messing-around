import os
from dotenv import load_dotenv

from langchain_core.documents import Document
from langchain_text_splitters import RecursiveCharacterTextSplitter
from langchain_chroma import Chroma
from langchain_google_genai import GoogleGenerativeAIEmbeddings
from langchain_classic.retrievers import ParentDocumentRetriever
from langchain_core.stores import InMemoryStore

load_dotenv()

# Embedding model
embeddings = GoogleGenerativeAIEmbeddings(model="models/gemini-embedding-001")

# Sample document for Parent-Child Retriever demo
long_doc = Document(
    page_content="""
# Complete Guide to Building AI Agents

## Chapter 1: Introduction to Autonomous AI Agents
AI agents are autonomous software systems that perceive their environment, make complex decisions, and execute multi-step actions to achieve user goals. Unlike static chatbots that only respond to immediate prompts, AI agents maintain persistent state, utilize external tools via API calls, and dynamically plan execution steps. Key architectural components of an AI agent include an LLM reasoning engine, long-term and short-term memory modules, specialized tool execution integrations, and reflective self-correction mechanisms.

## Chapter 2: Modern Agentic Frameworks & Ecosystems
Several frameworks exist for constructing stateful AI agents:
LangChain provides the foundational abstractions for prompt engineering, document loading, vector storage, and linear chains. It excels at straightforward tool-calling workflows and offers seamless integration across diverse LLM providers.
LangGraph extends LangChain specifically for building complex, multi-agent stateful systems. By modeling agent workflows as directed graphs, LangGraph enables cyclical loops, persistence, human-in-the-loop approvals, and fault-tolerant state recovery.
CrewAI focuses on role-based multi-agent collaboration, allowing teams of specialized agents with distinct personalities and tools to cooperate autonomously on complex enterprise tasks.

## Chapter 3: Production Engineering & Observability
Deploying AI agents into production requires strict operational safeguards:
1. Robust Error Handling: Implementing fallbacks, retry policies, and graceful degradation when API endpoints fail or rate limits are reached.
2. Token & Cost Optimization: Managing context window overhead through semantic chunking, prompt compression, and aggressive response caching.
3. Observability & Tracing: Using platforms like LangSmith to log full execution traces, inspect prompt inputs/outputs, monitor latency, and evaluate agent decision paths.
4. Security & Access Control: Sandboxing code execution tools, validating user authorization, and preventing prompt injection vulnerabilities.
""",
    metadata={"source": "ai_agents_guide.md"},
)


def demo_parent_child_retriever():
    #define parent and child chunkers
    parent_splitter = RecursiveCharacterTextSplitter(chunk_size = 800, chunk_overlap = 100)
    child_splitter = RecursiveCharacterTextSplitter(chunk_size = 200, chunk_overlap = 50)

    #define your parent and child stores
    vectorstore = Chroma(
        collection_name="child_chunks",
        embedding_function=embeddings
    )
    store = InMemoryStore()

    #define the retriever which will populate the store
    retriever = ParentDocumentRetriever(
        vectorstore=vectorstore,
        docstore=store,
        child_splitter=child_splitter,
        parent_splitter=parent_splitter
    )

    #queries
    queries = [
        "what does langgraph do?",
        "how does langsmith help?"
    ]

    retriever.add_documents([long_doc])

    #normal retrieves child
    print("=========CHILD RETRIEVEAL===========")
    for query in queries:
        child_docs = vectorstore.similarity_search(query)
        print(f"Query: {query}")
        print(f"Answer: {child_docs[0].page_content}")
        print()

    #parent chunk 
    print("=========PARENT RETRIEVAL==========")
    for query in queries:
        parent_docs = retriever.invoke(query)
        print(f"Query: {query}")
        print(f"Answer: {parent_docs[0].page_content}")
        print()




if __name__ == "__main__":
    demo_parent_child_retriever()
