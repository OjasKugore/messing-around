from langchain_text_splitters import (
    RecursiveCharacterTextSplitter,
    CharacterTextSplitter,
    TokenTextSplitter,
    MarkdownHeaderTextSplitter,
    Language
)
from langchain_core.documents import Document
from dotenv import load_dotenv

load_dotenv()

SAMPLE_TEXT = """# Introduction to Machine Learning

Machine learning is a subset of artificial intelligence that enables systems to learn and improve from experience without being explicitly programmed.

## Types of Machine Learning

### Supervised Learning
Supervised learning uses labeled data to train models. The algorithm learns to map inputs to outputs based on example input-output pairs.

Common algorithms include:
- Linear Regression
- Decision Trees
- Neural Networks

### Unsupervised Learning
Unsupervised learning finds hidden patterns in unlabeled data. The algorithm discovers structure without predefined labels.

Common algorithms include:
- K-Means Clustering
- Principal Component Analysis
- Autoencoders

## Applications

Machine learning is used in many fields:
1. Image recognition
2. Natural language processing
3. Recommendation systems
4. Fraud detection
5. Autonomous vehicles
""".strip()

SAMPLE_CODE = '''
def quicksort(arr):
    """
    Quicksort implementation in Python.
    Time complexity: O(n log n) average, O(n²) worst case.
    """
    if len(arr) <= 1:
        return arr

    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]

    return quicksort(left) + middle + quicksort(right)


def binary_search(arr, target):
    """
    Binary search implementation.
    Requires sorted array.
    Time complexity: O(log n)
    """
    left, right = 0, len(arr) - 1

    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return -1
'''
def recrusive_splitter():
    splitter = RecursiveCharacterTextSplitter(
        chunk_size = 500,
        chunk_overlap = 50,
        separators=["\n\n", "\n", " ", ""] 
    )
    chunks = splitter.split_text(SAMPLE_TEXT)

    print(f"Original Length: {len(SAMPLE_TEXT)} chars.")
    print(f"Number of chunks: {len(chunks)}")
    print(f"Chunk sizes: {[len(c) for c in chunks]}")
    print(f"First chunk preview: {chunks[0][:250]}...")

def overlap_importance():
    text = " a quick brown fox jumped over the lazy dog" * 10

    #without overlap
    splitter1 = RecursiveCharacterTextSplitter(
        chunk_size = 200,
        chunk_overlap = 0
    )
    #with overlap
    splitter2 = RecursiveCharacterTextSplitter(
        chunk_size = 200,
        chunk_overlap = 20
    )
    chunks1 = splitter1.split_text(text)
    chunks2 = splitter2.split_text(text)

    print("Without overlap")
    print(f"chunk 1 end: {chunks1[0][-20:]}")
    print(f"chunk 2 start: {chunks1[1][:20]}")

    print("With overlap")
    print(f"chunk 1 end: {chunks2[0][-20:]}")
    print(f"chunk 2 start: {chunks2[1][:20]}")

if __name__ == "__main__":
    overlap_importance()
