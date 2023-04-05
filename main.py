import pygame
import socket

pygame.init()

screen = pygame.display.set_mode((400, 400))

x = 200
y = 200

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('localhost', 9000))
sock.listen(1)
conn, addr = sock.accept()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()
        if event.type == pygame.MOUSEBUTTONDOWN:
            x, y = pygame.mouse.get_pos()
            conn.send(f"{x},{y}\n".encode())
    
    # Vérifier si des données sont envoyées par le contrôleur
    try:
        conn.settimeout(0.1)  # Temps d'attente maximal de 0.1 seconde
        data = conn.recv(1024)
        if data:
            x, y = data.decode().split(',')
            x, y = int(x), int(y)
    except socket.timeout:
        pass

    screen.fill((255, 255, 255))
    pygame.draw.circle(screen, (255, 0, 0), (x, y), 10)
    pygame.display.update()
