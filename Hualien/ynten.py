import pygame

pygame.init()

screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("測試")
red_square = pygame.surface.Surface((50, 50))
red_square.fill((255, 255, 255))

square = pygame.surface.Surface((50, 50))
square.fill((150, 150, 150))

red_square_rect = red_square.get_rect()
square_rect = square.get_rect()

red_square_rect.center = 400, 200
square_rect.center = 400, 400

screen.blit(red_square, red_square_rect)
screen.blit(square, square_rect)

pygame.display.flip()
clock = pygame.time.Clock()

while True:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
    red_square_rect = red_square_rect.move((0, 10))
    square_rect = square_rect.move((0, -10))
        
    if pygame.Rect.colliderect(red_square_rect, square_rect) == 1:
        red_square_rect = red_square_rect.move((0, -10))
        square_rect = square_rect.move((0, 10))

    if  red_square_rect.top < 0 :
        red_square_rect = red_square_rect.move((0, 10))
        
    if  square_rect.bottom > 600 :
        square_rect = square_rect.move((0, -10))
            
    screen.fill((0, 0, 0))  
    screen.blit(red_square, red_square_rect)
    screen.blit(square, square_rect)
    pygame.display.flip()
    clock.tick(60)