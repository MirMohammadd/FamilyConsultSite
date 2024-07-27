try:
    import mysql.connector
except:
    pass
class DatabaseConnector:
    def __init__(self, user, password, host, unix_socket, database, raise_on_warnings=True):
        self.config = {
            'user': user,
            'password': password,
            'host': host,
            'unix_socket': unix_socket,
            'database': database,
            'raise_on_warnings': raise_on_warnings
        }
        self.cnx = None
        self.cursor = None

    def connect(self):
        """Establish a database connection and create a cursor."""
        self.cnx = mysql.connector.connect(**self.config)
        self.cursor = self.cnx.cursor(dictionary=True)

    def disconnect(self):
        """Close the database connection and cursor."""
        if self.cursor:
            self.cursor.close()
        if self.cnx:
            self.cnx.close()

    def execute_query(self, query):
        """Execute a given SQL query."""
        self.cursor.execute(query)
        return self.cursor.fetchall()

    def use_database(self, database):
        """Switch to the specified database."""
        self.cursor.execute(f"USE {database};")

class AppointmentsDatabase(DatabaseConnector):
    def __init__(self, user, password, host, unix_socket, database, raise_on_warnings=True):
        super().__init__(user, password, host, unix_socket, database, raise_on_warnings)

    def fetch_appointments(self):
        """Fetch all appointments from the database."""
        self.use_database(self.config['database'])
        results = self.execute_query("SELECT * FROM Appointments;")
        return results

# Usage example:
if __name__ == "__main__":
    db = AppointmentsDatabase(
        user='root',
        password='root',
        host='localhost',
        unix_socket='/Applications/MAMP/tmp/mysql/mysql.sock',
        database='DailyConsults'
    )
    
    db.connect()
    appointments = db.fetch_appointments()
    for row in appointments:
        print(row)
    db.disconnect()
