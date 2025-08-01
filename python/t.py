import pygame

# Initialize pygame
pygame.init()

# Set up the display
screen = pygame.display.set_mode((800, 600))

# Create a player
player_image = pygame.image.load("player.png")
player_rect = player_image.get_rect()
player_rect.center = (400, 500)

# Create bullets
bullet_image = pygame.image.load("bullet.png")
bullet_rect = bullet_image.get_rect()
bullet_rect.center = player_rect.center
bullet_speed = 5
bullets = []

# Game loop
while running:
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                # Shoot a bullet
                bullet_rect = bullet_image.get_rect()
                bullet_rect.center = player_rect.center
                bullets.append(bullet_rect)

    # Update game logic
    for bullet in bullets:
        bullet.y -= bullet_speed
        if bullet.y < 0:
            bullets.remove(bullet)

    # Render graphics
    screen.fill((255, 255, 255))  # Fill the screen with white
    screen.blit(player_image, player_rect)  # Draw the player
    for bullet in bullets:
        screen.blit(bullet_image, bullet)  # Draw the bullets
    pygame.display.flip()  # Update the display

# Quit pygame
pygame.quit()
