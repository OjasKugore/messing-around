# Python Playground

A monorepo for Python experiments, managed with [uv](https://docs.astral.sh/uv/) workspaces.

## Projects

| Package / Directory | Description |
|---------------------|-------------|
| [`clitool/`](clitool/) | **DataShift CLI** — a database migration and sync tool built with [Typer](https://typer.tiangolo.com/) and [Rich](https://rich.readthedocs.io/) |
| [`rag/`](rag/) | **RAG Pipeline & Retrieval Experiments** — LangChain, ChromaDB, Gemini LLM/embeddings demos including semantic chunking, parent-child retrieval, hybrid search, and contextual compression |
| [`dsa/`](dsa/) | **C & Data Structures / Systems Foundations** — C fundamentals including pointers (Pass-by-Value vs. Pass-by-Reference), array decay, structs, arrays of structs, and learning roadmap |
| [`AST/`](AST/) | **Abstract Syntax Tree (AST) Exploration** — Python AST analysis scripts and custom NodeVisitors |

## Getting Started

```bash
# Install uv if you haven't already
curl -LsSf https://astral.sh/uv/install.sh | sh

# Install all workspace dependencies
uv sync --all-packages
```

## Running the CLI tool

```bash
uv run --package clitool clitool --help
uv run --package clitool clitool db status
uv run --package clitool clitool db migrate db_a db_b
```

## Running the RAG pipeline & experiments

```bash
# Copy the example env file and fill in your API keys
cp rag/.env.example rag/.env

# Run basic RAG demo
uv run --package rag python rag/app.py

# Run retrieval & chunking experiments
uv run --package rag python rag/semantic_chunking.py
uv run --package rag python rag/parent_child_retriever.py
uv run --package rag python rag/hybrid_search.py
uv run --package rag python rag/contextual_compression.py
```

## C & Data Structures (dsa)

```bash
# Compile and run any C program in dsa/
cd dsa
gcc struct_basics.c -o struct_basics && ./struct_basics
gcc passing_array.c -o passing_array && ./passing_array
gcc pbv_pbr.c -o pbv_pbr && ./pbv_pbr
```

## Repo structure

```
.
├── AST/                      # Python AST parser & visitor scripts
│   └── ast_main.py
├── clitool/                  # DataShift CLI package
│   ├── clitool.py
│   ├── pyproject.toml
│   └── README.md
├── dsa/                      # C & DSA practice modules
│   ├── c_learning_roadmap.md
│   ├── pbv_pbr.c             # Pass by value & reference
│   ├── passing_array.c       # Passing array elements & array decay
│   └── struct_basics.c       # Structs, PBR/PBV, arrays of structs
├── rag/                      # RAG pipeline package
│   ├── app.py                # Core RAG pipeline demo
│   ├── contextual_compression.py
│   ├── document_loaders.py   # Document loading helpers
│   ├── embeddings_deep.py    # Similarity & dot-product search demo
│   ├── hybrid_search.py      # Keyword + dense retrieval
│   ├── langsmith_demo.py     # Observability with LangSmith
│   ├── parent_child_retriever.py
│   ├── semantic_chunking.py  # Semantic vs recursive splitting
│   ├── text_splitters.py
│   ├── docs/
│   ├── pyproject.toml
│   └── README.md
├── pyproject.toml            # uv workspace root
├── uv.lock                   # Single lockfile for the entire workspace
└── .gitignore
```
<img width="400" height="400" alt="39hvucmkymma1" src="https://github.com/user-attachments/assets/f66fb61a-1b0b-49d9-82e9-e2694ddfdce0" />
