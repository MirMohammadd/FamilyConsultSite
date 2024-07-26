#!/usr/bin/env /Applications/MAMP/Library/bin/python

import mysql.connector

config = {
  'user': 'root',
  'password': 'root',
  'host': 'localhost',
  'unix_socket': '/Applications/MAMP/tmp/mysql/mysql.sock',
  'database': 'DailyConsults',
  'raise_on_warnings': True
}

cnx = mysql.connector.connect(**config)

cursor = cnx.cursor(dictionary=True)

cursor.execute("USE DailyConsults;")
cursor.execute("INSERT INTO Appointments VALUES ('jack', 'doe', 'jack@com', '2012-04-30')")
cursor.execute("SELECT * FROM Appointments;")

results = cursor.fetchall()

for row in results:
    print(row)

cnx.close()

