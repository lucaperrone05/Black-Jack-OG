import sqlite3

conn = sqlite3.connect("blackjack.db")
cursor = conn.cursor()

cursor.execute("SELECT password FROM utenti;")
for row in cursor.fetchall():
    print(row[0].encode('latin1').decode('utf-8', errors='replace'))  # Prova diverse codifiche

conn.close()
