"""
UNFINISHED - KEEP EXPLORING
"""


import ast

class AuditVisitor(ast.NodeVisitor):
    def visit_FunctionDef(self, node):
        docstring = ast.get_docstring(node)
        if not docstring:
            print(f"Line {node.lineno}: Function '{node.name}' has no docstring.")
            
        # Continue traversing child nodes inside the function body
        self.generic_visit(node)

    def visit_Import(self, node):
        for alias in node.names:
            print(f"Line {node.lineno}: Found import '{alias.name}'")

source = """
import os
import sys

def calculate_total(x, y):
    return x + y

def fetch_user(user_id):
    \"\"\"Retrieves user record from database.\"\"\"
    pass
"""

tree = ast.parse(source)
visitor = AuditVisitor()
visitor.visit(tree)