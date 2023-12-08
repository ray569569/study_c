import pygame.font

class Cell:
    def __init__(self, num) -> None:
        self.width, self.height = 100, 100
        self.button_color = (200, 200, 200)
        self.text_color = (20, 20, 20)
        self.font = pygame.font.SysFont(None, 48)

        self.rect = pygame.Rect(0, 0, self.width, self.height)
        self.num = num
        self.num_str = str(self.num)
        self.is_click = False
        self.update_color()
    
    def update_color(self):
        self.num_img = self.font.render(self.num_str, True, self.text_color, self.button_color)
        self.num_img_rect = self.num_img.get_rect()
        self.num_img_rect.center = self.rect.center
