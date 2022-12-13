from flask import Flask, request, jsonify

app = Flask(__name__)


@app.route('/helloworld')  # test api
def helloworld():
    return 'Hello, World!'


@app.route('/test', methods=['POST'])  # post echo api
def test():
    param = request.get_json()
    print(param)
    return jsonify(param)


if __name__ == "__main__":
    app.run(host='0.0.0.0')
