from flask import Flask, render_template
from flask.globals import request

app = Flask(__name__) # refers to the name of the current file

@app.route("/")
def index():
    return render_template("index.html", name=request.args.get("name", "world")) # Parses the 'name' http variable

@app.route("/greet")
def greet():
    return "TODO" # render_template("index.html", name=request.args.get("name", "world")) # Parses the 'name' http variable