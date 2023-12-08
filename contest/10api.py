import psycopg2
import json
import time
#from django.db import transaction
from flask_cors import CORS
from flask import Flask, request
from flask import jsonify
app = Flask(__name__)

#設定資料庫連接
#conn = psycopg2.connect(host = "makereal.local", port="5432",user="ray", database="ray")
conn = psycopg2.connect('dbname=ray')
cur = conn.cursor()

def getsensor(name,page):
    cur.execute("select * from sensor where sensor = %s offset %s row fetch next 50 rows only", (name, page, ))
    return cur.fetchall()

def getcitizen(rank):
    cur.execute("select * from citizen where rank = %s",(rank,))
    return cur.fetchall()

CORS(app)
@app.route("/")
def hello():
    return "HELLO OAO"

#感測器傳資料
@app.route('/sensor_store_data/', methods=['POST'])
def sensor_store_data():
    data = request.json  
    if data:
        #data={'nae':'4','state':'4','value':45}
        try:
            arg=(data['name'], data['state'], data['value'])
        except:
            return "400 Bad Request (missing column)", 400
        try:
            cur.execute("""INSERT INTO sensor (sensor,state,value,workercheck,time) VALUES (%s, %s, %s, false, current_timestamp)""",
                        (data['name'], data['state'], data['value']))
        except:
            return "500 internal server error", 500
        cur.execute("""INSERT INTO sensor (sensor,state,value,workercheck,time) VALUES (%s, %s, %s, false, current_timestamp)""",
                    (data['name'], data['state'], data['value']))
        conn.commit()
        return "200 OK",200
    else:
        return "400 Bad Request (missing fields)", 400
        
#工人確認
@app.route('/worker_store_data/', methods=['POST'])
def worker_store_data():
    data = request.json
    if data:
        try:
            arg=(data['workercheck'], )
        except:
            return "400 Bad Request (missing column)", 400
        try:
            cur.execute("""UPDATE sensor SET workercheck = %s, workerchecktime = current_timestamp WHERE workercheck=false""",
                        (data['workercheck'], ))
        except:
            return "500 internal server error", 500
        cur.execute("""UPDATE sensor SET workercheck = %s, workerchecktime = current_timestamp WHERE workercheck=false""",
                    (data['workercheck'],))
        conn.commit()
        return "200 OK",200
    else:
        return "400 Bad Request (missing fields)", 400
#政府處理
@app.route('/government_store_sensor_data/', methods = ['POST'])
def government_store_sensor_data():
    data = request.json  
    if data:
        try:
            arg=(data['person'],data['government'],data['name'])
        except:
            return "400 Bad Request (missing column)", 400
        try:
            cur.execute("""UPDATE sensor SET person=%s,government = %s,governmenttime = current_timestamp WHERE name = %s and state = true""",
                        arg)
        except:
            return "500 internal server error", 500
        cur.execute("""UPDATE sensor SET person=%s,government = %s,governmenttime = current_timestamp WHERE name = %s and state = false""",
                    (data['person'],data['government'],data['name']))    
        conn.commit()
        return "200 OK",200
    else:
        return "400 Bad Request (missing fields)", 400
#人民傳資料
@app.route('/citizen_store_data', methods = ['POST'])
def citizen_store_data():
    data = request.json 
    if data:
        try:
            arg=(data['name'], data['time'], data['place'],data['phone'],data['type'], data['detail'])
        except:
            return "400 Bad Request (missing column)", 400
        try:
            cur.execute("""INSERT INTO citizen VALUES(%s, %s, %s, %s, %s,false)""",
                        (data['name'], data['time'], data['place'],data['phone'],data['type'], data['detail']))
        except:
            return "500 internal server error", 500
        cur.execute("""INSERT INTO citizen VALUES(%s, %s, %s, %s, %s,false)""",
                    (data['name'], data['time'], data['place'],data['phone'],data['type'], data['detail']))
        conn.commit()
        return "200 OK",200
    else:
        return "400 Bad Request (missing fields)", 400
        
@app.route('/government_store_citizen_data/', methods = ['POST'])
def government_store_citizen_data():
    data = request.json
    if data:
        try:
            arg=(data['state'],data['person'],data['outcome'],data['rank'])
        except:
            return "400 Bad Request (missing column)", 400
        try:
            cur.execute("""UPDATE citizen SET state = %s,person=%s, dealingtime = current_timestamp,outcome = %s WHERE rank = %s """,
                        (data['state'],data['person'],data['outcome'],data['rank']))
        except:
            return "500 internal server error", 500
        cur.execute("""UPDATE citizen SET state = %s,person=%s, dealingtime = current_timestamp,outcome = %s WHERE rank = %s """,
                    (data['state'],data['person'],data['outcome'],data['rank']))
        conn.commit()
        return "200 OK",200
    else:
        return "400 Bad Request (missing fields)", 400
#網頁拿資料

@app.route('/get_sensor_data/', methods = ['GET'])
def get_sensor_data():
    data=request.args
    if(data):
        #data={'name':'water','page':'4'}
        try:
            page = int(data['page'])*50
            arg = (data['name'], data['page'])
        except:
            return "400 Bad Request (missing column)", 400
        
        try:
            cur.execute("select * from sensor where sensor = %s offset %s row fetch next 50 rows only", (data['name'], data['page'], ))
        except:
            return "500 internal server error", 500
        
        temp = getsensor(data['name'],int(data['page'])*50)
        name = ['sensor', 'state', 'value', 'workercheck', 'person','workerchecktime','time','government','governmenttime']
        final=[]
        dir = {}
        for i in range(0,len(temp)):
            for j in range(0,9):
                dir[name[j]] = temp[i][j]
            final.append(dir)
            dir = {}
        return final,200
    else:
        return "400 Bad Request (missing fields)", 400
        
@app.route('/get_citizen_data/', methods = ['GET'])
def get_citizen_data():
    data=request.args
    if(data):
#        data={'rank':'4','page':'4'}
        try:
            arg=(data['rank'])
        except:
            return "400 Bad Request (missing column)", 400
        try:
            cur.execute("select * from citizen where rank = %s",(data['rank'], ))
        except:
            return "500 internal server error", 500
        
        temp = getcitizen(data['rank'])
        label = ['name', 'time', 'place', 'phone', 'type', 'detail','state', 'person','dealingtime','outcome','rank']
        dir = {}
        for i in range(len(label)):
            dir[label[i]] = temp[0][i]
        return dir,200
    else:
        return "400 Bad Request (missing fields)", 400
if __name__ == "__main__":
    app.run(port=8080, host='0.0.0.0')