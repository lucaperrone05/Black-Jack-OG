import sqlite3

conn = sqlite3.connect("blackjack.db")
cursor = conn.cursor()

cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
print("Tabelle:", cursor.fetchall())

cursor.execute("SELECT * FROM utenti;")
for row in cursor.fetchall():
    print(row)

conn.close()

