import argparse
import os
import tempfile
from pathlib import Path

from dotenv import load_dotenv
from langchain_community.document_loaders import TextLoader, PyPDFLoader

load_dotenv()

# Default PDF path relative to this file
_DEFAULT_PDF = Path(__file__).parent / "docs" / "sample.pdf"


def load_text_file():
    """Load a temporary text file to demonstrate the TextLoader."""
    with tempfile.NamedTemporaryFile(delete=False, suffix=".txt") as temp_file:
        temp_file.write(
            b"Hello. This is a temporary sample text file.\n"
            b"This file is used to test out my document loading."
        )
        temp_file_path = temp_file.name

    try:
        loader = TextLoader(temp_file_path)
        documents = loader.load()

        print(f"Loaded {len(documents)} text document(s)")
        print(f"Metadata key count: {len(documents[0].metadata)}")
        print(f"Content preview: {documents[0].page_content[:100]}")
    finally:
        os.remove(temp_file_path)


def pdf_loader(pdf_path: str):
    """Load a PDF file and print a preview of each page."""
    loader = PyPDFLoader(pdf_path)
    documents = loader.load()

    print(f"Loaded {len(documents)} documents from PDF")
    for i, doc in enumerate(documents):
        print(f"Document {i+1} preview: {doc.page_content[:50]}")
        print(f"Metadata: {doc.metadata}")
        print("------------------------")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="LangChain document loader demo")
    parser.add_argument(
        "pdf_path",
        nargs="?",
        default=str(_DEFAULT_PDF),
        help="Path to the PDF file to load (default: docs/sample.pdf)",
    )
    args = parser.parse_args()
    pdf_loader(args.pdf_path)