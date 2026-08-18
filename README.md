# Python Playground

A monorepo for Python experiments, managed with [uv](https://docs.astral.sh/uv/) workspaces.

## Projects

| Package | Description |
|---------|-------------|
| [`clitool/`](clitool/) | **DataShift CLI** — a database migration and sync tool built with [Typer](https://typer.tiangolo.com/) and [Rich](https://rich.readthedocs.io/) |
| [`rag/`](rag/) | **RAG Pipeline** — a Retrieval-Augmented Generation demo built with [LangChain](https://python.langchain.com/) and ChromaDB |

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

## Running the RAG pipeline

```bash
# Copy the example env file and fill in your API keys
cp rag/.env.example rag/.env

uv run --package rag python rag/app.py
```

## Repo structure

```
.
├── clitool/                  # DataShift CLI package
│   ├── clitool.py
│   ├── pyproject.toml
│   └── README.md
├── rag/                      # RAG pipeline package
│   ├── app.py
│   ├── document_loaders.py
│   ├── docs/
│   ├── pyproject.toml
│   └── README.md
├── pyproject.toml            # uv workspace root
├── uv.lock                   # Single lockfile for the entire workspace
└── .gitignore
```
<img width="400" height="400" alt="39hvucmkymma1" src="https://github.com/user-attachments/assets/f66fb61a-1b0b-49d9-82e9-e2694ddfdce0" />
