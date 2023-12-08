import pygame

pygame.init()

screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("測試")

red_square = pygame.surface.Surface((50, 50))
red_square.fill((255, 0, 0))
red_square_rect = red_square.get_rect()
red_square_rect.center = 400, 400

white_square = pygame.surface.Surface((50, 50))
white_square.fill((255, 255, 255))
white_square_rect = red_square.get_rect()
white_square_rect.center = 400, 200

screen.blit(red_square, red_square_rect)
screen.blit(white_square, white_square_rect)

pygame.display.flip()
clock = pygame.time.Clock()
a = -2
b = 1
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
    red_square_rect = red_square_rect.move((0, a))
    white_square_rect = white_square_rect.move((0, b))

    if pygame.Rect.colliderect(red_square_rect, white_square_rect):
        a = -a
        b = -b
    if white_square_rect.top < 0:
        b = -b
    if red_square_rect.bottom > 600:
        a = -a

    screen.fill((0, 0, 0))
    screen.blit(red_square, red_square_rect)
    screen.blit(white_square, white_square_rect)
    pygame.display.flip()
    clock.tick(60)
