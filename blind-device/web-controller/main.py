from flask import Flask, request
from core import


app = Flask(__name__)


@app.route('/<int:select>')
def get_number(select):
