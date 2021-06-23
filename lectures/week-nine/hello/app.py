from flask import Flask, render_template
from flask.globals import request

app = Flask(__name__) # refers to the name of the current file

@app.route("/")
def index():
    # <param passed to template> = request.args.get(<http param>, <default>) 
    return render_template("/index.html") 

# Defaults to GET, need to specify for a POST etc
@app.route("/greet", methods=["POST"])
def greet():
    return render_template("/greet.html", name=request.form.get("name", "world")) # Parses the 'name' http variable

