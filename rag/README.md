# RAG Pipeline

A Retrieval-Augmented Generation (RAG) demo using [LangChain](https://python.langchain.com/), ChromaDB, and the Google Gemini API.

## What it does

- Splits a knowledge base into chunks and embeds them with `gemini-embedding-2-preview`
- Stores embeddings in a local [ChromaDB](https://www.trychroma.com/) vector store
- Answers questions using a Gemini LLM, grounded only in the retrieved context

## Setup

```bash
# From the repo root
uv sync --package rag

# Create your .env file
cp rag/.env.example rag/.env
# Then set GOOGLE_API_KEY (and optionally OPENAI_API_KEY) in rag/.env
```

## Usage

```bash
# Run the basic RAG demo
uv run --package rag python rag/app.py

# Load and inspect a PDF document
uv run --package rag python rag/document_loaders.py docs/sample.pdf
```

## Project structure

```
rag/
├── app.py               # Basic RAG pipeline demo
├── document_loaders.py  # TextLoader and PyPDFLoader helpers
├── docs/                # Sample documents (e.g. sample.pdf)
├── pyproject.toml
└── README.md
```
