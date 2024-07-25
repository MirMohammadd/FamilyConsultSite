import mysql.connector

# Replace these with your actual MySQL credentials
config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'port': 3306,
    'database': 'your_database'
}

try:
    # Establish the connection
    connection = mysql.connector.connect(**config)
    
    # Create a cursor object using the connection
    cursor = connection.cursor()
    
    # Example query
    cursor.execute("SELECT DATABASE();")
    db = cursor.fetchone()
    print("You're connected to database:", db)

except mysql.connector.Error as err:
    print("Error:", err)

finally:
    if connection.is_connected():
        cursor.close()
        connection.close()
        print("Connection closed.")
