'''
Langsmith setup and observability
production monitoring for langchain/langgraph
'''

import os
from langchain_google_genai import ChatGoogleGenerativeAI
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.output_parsers import StrOutputParser
from langsmith import traceable
from dotenv import load_dotenv

load_dotenv()

os.environ["LANGSMITH_TRACING"] = "true"
os.environ["LANGSMITH_PROJECT"] = "multi-agent-research"


@traceable(name="basic_chaining ")
def demo():
    '''Basic langsmith tracing'''
    llm = ChatGoogleGenerativeAI(model="gemini-3.6-flash")
    prompt = ChatPromptTemplate.from_template("Explain {topic} in one sentence.")

    chain = prompt | llm | StrOutputParser()

    print("Basic Tracing Demo:\n")
    print("Running chain with LangSmith tracing enabled...")

    result = chain.invoke({"topic": "machine learning"})

    print(f"Result: {result}")
    print("\nCheck LangSmith dashboard for trace details")

@traceable(name="named_runs_demo", tags=["production", "summarization"])
def demo_named_runs(): ##demonstrates how tagging helps later in langsmith
    """Name your runs for easier identification"""
    llm = ChatGoogleGenerativeAI(model="gemini-3.6-flash")

    prompt = ChatPromptTemplate.from_template("Summarize: {text}")

    chain = prompt | llm | StrOutputParser()

    print(f"\nNamed run demo:\n")

    result = chain.invoke(
        {"text": "LangSmith provides observability for LLM applications."}
    )

    print(f"Results: {result}")

    print("Run tagged with 'production', 'summarization'.")

@traceable(name="trace_with_metadata_demo", tags=["metadata", "filtering"])
def demo_metadata(user_id: str, request_type: str):
    """Add metadata to traces for filtering"""

    llm = ChatGoogleGenerativeAI(model="gemini-3.6-flash")

    result = llm.invoke(f"Hello from user {user_id} requesting {request_type}")

    return result.content


if __name__ == "__main__":
    demo()
    res = demo_metadata("user_123", "summarization")
    print(f"\nMetadata Demo Result: {res}")
    demo_named_runs()
