from flask import Flask, jsonify
import json

with open('data.json', 'r') as file:
    json_data = json.load(file)

app = Flask(__name__)

@app.route('/menus')
def order():
    return jsonify(json_data)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port="5000")