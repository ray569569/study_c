import pygame
import random
from cell import Cell
pygame.init()

screen = pygame.display.set_mode((600, 600))
pygame.display.set_caption("Test")
screen.fill((230, 230, 230))
pygame.display.flip()
clock = pygame.time.Clock()
is_click = False

cells = []

bingo = list(range(1, 26))
random.shuffle(bingo)

for i in range(0, 5):
    for j in range(0, 5):
        cell = Cell(bingo[i * 5 + j])
        cell.rect.x = 10 + j * 120
        cell.rect.y = 10 + i * 120
        cells.append(cell)

bingo = list(range(1, 26))

while True:
    clock.tick(60)
    is_click = False
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
        if event.type == pygame.MOUSEBUTTONDOWN:
            is_click = True

    mouse_pos = pygame.mouse.get_pos()
    mouse_buttons = pygame.mouse.get_pressed()
    
    for cell in cells:
        if cell.rect.collidepoint(mouse_pos):
            if is_click:
                cell.is_click = not cell.is_click
            cell.button_color = (230, 230, 200)
        else:
            cell.button_color = (200, 200, 200)
        if cell.is_click:
            cell.button_color = (230, 200, 200)
        
        cell.update_color()

        screen.fill(cell.button_color, cell.rect)
        screen.blit(cell.num_img, cell.num_img_rect)

    pygame.display.flip()
