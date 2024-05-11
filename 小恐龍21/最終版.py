import pygame
import os
import random
import sys

pygame.init()

# Global Constants
window_height = 600  # 視窗高度
window_width = 1100  # 視窗寬度

# 建立視窗
window = pygame.display.set_mode((window_width, window_height))

# 顏色
WHITE = pygame.Color(255, 255, 255)
BLACK = pygame.Color(0, 0, 0)

# Load 圖檔

RUNNING_LIST = [pygame.image.load(os.path.join("Assets/Dino", "DinoRun1.png")),
                pygame.image.load(os.path.join("Assets/Dino", "DinoRun2.png"))]
JUMPING_IMG = pygame.image.load(os.path.join("Assets/Dino", "DinoJump.png"))
DUCKING_LIST = [pygame.image.load(os.path.join("Assets/Dino", "DinoDuck1.png")),
                pygame.image.load(os.path.join("Assets/Dino", "DinoDuck2.png"))]

SMALL_CACTUS_LIST = [pygame.image.load(os.path.join("Assets/Cactus", "SmallCactus1.png")),
                     pygame.image.load(os.path.join("Assets/Cactus", "SmallCactus2.png")),
                     pygame.image.load(os.path.join("Assets/Cactus", "SmallCactus3.png"))]

LARGE_CACTUS_LIST = [pygame.image.load(os.path.join("Assets/Cactus", "LargeCactus1.png")),
                     pygame.image.load(os.path.join("Assets/Cactus", "LargeCactus2.png")),
                     pygame.image.load(os.path.join("Assets/Cactus", "LargeCactus3.png"))]

BIRD_LIST = [pygame.image.load(os.path.join("Assets/Bird", "Bird1.png")),
             pygame.image.load(os.path.join("Assets/Bird", "Bird2.png"))]

CLOUD = pygame.image.load(os.path.join("Assets/Other", "Cloud.png"))

# Load 步道

BG = pygame.image.load(os.path.join("Assets/Other", "Track.png"))
BG1 = pygame.image.load(os.path.join("Assets/Other", "Track.png"))



# Class
# 文字物件
class Text:
    def __init__(self, text : str, size : int, color : pygame.Color, position=(0, 0)):
        self.font = pygame.font.SysFont('freesansbold.ttf', size)  # 字體大小(參數)與字型
        self.surface = self.font.render(text, True, color)  # 印出的字串(參數)與呈現
        self.rect = self.surface.get_rect()  # 文字框起
        self.rect.center = position  # 文字的中心位置(參數)
        # 請在此輸入您的程式碼
        # 請在此輸入您的程式碼
        # 請在此輸入您的程式碼
        # 請在此輸入您的程式碼

    def draw(self, screen : pygame.display):
        # 請在此輸入您的程式碼
        screen.blit(self.surface, self.rect)

# 雲朵物件
class Cloud:
    def __init__(self):
        self.image = CLOUD  # 載入雲朵圖
        self.x = window_width + random.randint(800, 1000)  # 將雲朵初始位置設在視窗外隨機800到1000
        self.y = random.randint(50, 100)  # 隨機設置雲朵高度
        self.width = self.image.get_width()  # 以變數存雲朵寬度

    def update(self):
        self.x -= game_speed
        if self.x < -self.width:  # 若雲朵開始走道左邊視窗盡頭並消失
            self.x = window_width + random.randint(2500, 3000)  # 則將雲朵位置重新設在視窗外隨機800到1000
            self.y = random.randint(50, 100)

    def draw(self, screen : pygame.display):
        screen.blit(self.image, (self.x, self.y))

# 恐龍物件
class Dinosaur:
    Y_Line = 1
    X_POS = 80
    Y_POS = 460
    Y_POS2 = 160
    Y_POS_DUCK = 490
    Y_POS_DUCK2 = 190
    JUMP_VEL = 7
    JUMP_VEL2 = 6
    # 初始化
    def __init__(self):

        # 定義變數
        self.dino_duck = False
        self.dino_run = True
        self.dino_jump = False
        self.dino_jump2 = False
        self.step_index = 0  # 腳步動畫
        self.jump_vel = self.JUMP_VEL  # 跳上、下的速度
        self.jump_vel2 = self.JUMP_VEL2
        # Load 圖檔
        self.duck_img_list = DUCKING_LIST
        self.run_img_list = RUNNING_LIST
        self.jump_img = JUMPING_IMG
        self.image = self.run_img_list[0]  # 恐龍跑的第一步

        # 把恐龍腳色框列
        self.dino_rect = self.image.get_rect()
        self.dino_rect.x = self.X_POS
        self.dino_rect.y = self.Y_POS

    def run(self):
        self.image = self.run_img_list[self.step_index // 5]  # 依 step_index 決定恐龍的跑步圖片，每五個step_index換一張圖
        self.dino_rect = self.image.get_rect()
        self.dino_rect.x = self.X_POS
        if self.Y_Line==1:
            self.dino_rect.y = self.Y_POS
        else:
            self.dino_rect.y = self.Y_POS2
        self.step_index += 1

    def duck(self):
        self.image = self.duck_img_list[self.step_index // 5]  # 依 step_index 決定恐龍的蹲下圖片，每五個step_index換一張圖
        self.dino_rect = self.image.get_rect()
        self.dino_rect.x = self.X_POS
        if self.Y_Line==1:
            self.dino_rect.y = self.Y_POS_DUCK
        else:
            self.dino_rect.y = self.Y_POS_DUCK2
        self.step_index += 1

    def jump(self):
        self.image = self.jump_img
        if self.dino_jump:
            self.dino_rect.y -= self.jump_vel * 4  # 依目前的跳躍速度來移動小恐龍的y座標值
            self.jump_vel -= 0.5  # 若jump_vel小於0則代表小恐龍逐漸往下掉
        if self.jump_vel < - self.JUMP_VEL:
            self.dino_jump = False
            self.jump_vel = self.JUMP_VEL
    def jump2(self):
        self.image = self.jump_img
        if self.Y_Line==1:
            if self.dino_jump2:
                self.dino_rect.y -= self.jump_vel2 * 8  # 依目前的跳躍速度來移動小恐龍的y座標值
                self.jump_vel2 -= 0.5  # 若jump_vel小於0則代表小恐龍逐漸往下掉
            if self.jump_vel2==-1.5:
                self.dino_rect.y=160
                self.dino_jump2 = False
                self.jump_vel2=self.JUMP_VEL2
                self.Y_Line=2
        else:
            if self.dino_jump2:
                self.dino_rect.y += self.jump_vel2 * 8  # 依目前的跳躍速度來移動小恐龍的y座標值
                self.jump_vel2 -= 0.5  # 若jump_vel小於0則代表小恐龍逐漸往下掉
            if self.jump_vel2==1.5:
                self.dino_rect.y=460
                self.dino_jump2 = False
                self.jump_vel2=self.JUMP_VEL2
                self.Y_Line=1
            

    # 更新動作
    def update(self, user_input : pygame.key ):
        if user_input[pygame.K_UP] and not self.dino_jump and not self.dino_jump2:
            self.dino_duck = False
            self.dino_run = False
            self.dino_jump = True
            self.dino_jump2 = False
        elif user_input[pygame.K_DOWN] and not self.dino_jump and not self.dino_jump2:
            self.dino_duck = True
            self.dino_run = False
            self.dino_jump = False
            self.dino_jump2 = False
        elif user_input[pygame.K_RIGHT] and not self.dino_jump and not self.dino_jump2:
            self.dino_duck = False
            self.dino_run = False
            self.dino_jump = False
            self.dino_jump2 = True
        elif not (self.dino_jump or user_input[pygame.K_DOWN] or user_input[pygame.K_RIGHT] or self.dino_jump2):
            self.dino_duck = False
            self.dino_run = True
            self.dino_jump = False
            self.dino_jump2 = False

        # 以變數判斷小恐龍目前該做甚麼動作
        if self.dino_duck:
            self.duck()
        if self.dino_run:
            self.run()
        if self.dino_jump:
            self.jump()
        if self.dino_jump2:
            self.jump2()
        if self.step_index >= 10:
            self.step_index = 0

    def draw(self, screen : pygame.display):
        screen.blit(self.image, (self.dino_rect.x, self.dino_rect.y))

class Obstacle:
    def __init__(self, imageList : list, typeObject : int):
        self.image_list = imageList  # 以變數儲存障礙物類型
        self.type = typeObject  # 以變數儲存障礙物樣貌
        self.rect = self.image_list[self.type].get_rect()  # 將障礙物框起
        self.rect.x = window_width  # 障礙物X座標位置
        
    

    def update(self):
        self.rect.x -= game_speed
        

    def draw(self, screen : pygame.display):
        screen.blit(self.image_list[self.type], (self.rect.x, self.rect.y))

class LargeCactus(Obstacle):
    def __init__(self, image_list : list):
        self.type = random.randint(0, 2)  # 三種大仙人掌型態隨機選取一種
        super().__init__(image_list, self.type)  # 繼承障礙物屬性與動作
        self.rect.y = 448  # Y座標位置

class SmallCactus(Obstacle):
    def __init__(self, image_list : list):
        self.type = random.randint(0, 2)  # 三種小仙人掌型態隨機選取一種
        super().__init__(image_list, self.type)  # 繼承障礙物屬性與動作
        self.rect.y = 473 # Y座標位置

class Bird(Obstacle):
    def __init__(self, image_list : list):
        self.type = random.randint(0, 1)
        super().__init__(image_list, self.type)  # 繼承障礙物屬性與動作
        self.rect.y = 413  # Y座標位置

class LargeCactus1(Obstacle):
    def __init__(self, image_list : list):
        self.type = random.randint(0, 2)  # 三種大仙人掌型態隨機選取一種
        super().__init__(image_list, self.type)  # 繼承障礙物屬性與動作
        self.rect.y = 148 # Y座標位置

class SmallCactus1(Obstacle):
    def __init__(self, image_list : list):
        self.type = random.randint(0, 2)  # 三種小仙人掌型態隨機選取一種
        super().__init__(image_list, self.type)  # 繼承障礙物屬性與動作
        self.rect.y = 173  # Y座標位置

class Bird1(Obstacle):
    def __init__(self, image_list : list):
        self.type = random.randint(0, 1)
        super().__init__(image_list, self.type)  # 繼承障礙物屬性與動作
        self.rect.y = 113  # Y座標位置




# 開始/結算畫面
def menu(death : bool):
    death_text_position = (window_width // 2, window_height // 2)  # 死亡文字顯示的座標位置
    dino_position = (window_width // 2 - 20, window_height // 2 - 140)  # 恐龍顯示的座標位置

    run = True
    while run:
        window.fill(WHITE)
        if death == False:
            start_text = Text("Press Space to Start", 40, BLACK, death_text_position)

        elif death == True:
            score_text_position = (window_width // 2, window_height // 2 + 50)
            start_text = Text("Press Space to Restart", 40, BLACK, death_text_position)
            score_text = Text("Your Score: " + str(points), 40, BLACK, score_text_position)
            score_text.draw(window)
        
        start_text.draw(window)
        window.blit(RUNNING_LIST[0], dino_position)
        pygame.display.update()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    main()
                elif event.key == pygame.K_ESCAPE:
                    run = False
    pygame.quit()
    sys.exit()

# 遊戲進行
def main() :
    #變數
    global game_speed
    game_speed = 15 # 背景移動速度
    x_pos_bg = 0    # 背景x座標
    y_pos_bg = 530  # 背景y座標
    
    x_pos_bg1 = 0    # 背景x座標
    y_pos_bg1 = 230  # 背景y座標
    
    # 分數(變數)
    global points
    points = 0
    
    # 時鐘(變數)
    clock = pygame.time.Clock()

    # 雲朵(變數)
    cloud = Cloud()
    
    # 小恐龍(變數)
    player = Dinosaur()
    
    # 障礙物串列
    obstacles2 = []  # 障礙物串列(list)

    run = True
    while run:
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
        
        # 塗白
        window.fill(WHITE)
        
        # 背景
        image_width = BG.get_width()
        window.blit(BG, (x_pos_bg, y_pos_bg))
        window.blit(BG, (image_width + x_pos_bg, y_pos_bg))
        x_pos_bg -= game_speed  # 使背景移動
        if x_pos_bg <= -image_width:
            window.blit(BG, (image_width + x_pos_bg, y_pos_bg))
            x_pos_bg = 0
            
        image_width = BG1.get_width()
        window.blit(BG1, (x_pos_bg1, y_pos_bg1))
        window.blit(BG1, (image_width + x_pos_bg1, y_pos_bg1))
        x_pos_bg1 -= game_speed  # 使背景移動
        if x_pos_bg1 <= -image_width:
            window.blit(BG, (image_width + x_pos_bg1, y_pos_bg1))
            x_pos_bg1 = 0
        # 雲朵
        cloud.update()
        cloud.draw(window)
        
        # 分數   
        points += 1
        if points % 100 == 0:
            game_speed += 0.7
        text_position = (1000, 40)
        text = Text("Points: " + str(points), 30, BLACK, text_position)
        text.draw(window)
        
        
        # 小恐龍
        user_input = pygame.key.get_pressed()  # 接收玩家指令
        player.update(user_input)  # 依據玩家指令更新恐龍的動作
        player.draw(window)  # 將恐龍換上
    
        # 障礙物
        if len(obstacles2) == 0:
            rand = random.randint(0, 5)
            if rand == 0:
                obstacles2.append(SmallCactus(SMALL_CACTUS_LIST))
            elif rand == 1:
                obstacles2.append(LargeCactus(LARGE_CACTUS_LIST))
            elif rand == 2:
                obstacles2.append(Bird(BIRD_LIST))
            elif rand == 3:
                obstacles2.append(SmallCactus1(SMALL_CACTUS_LIST))
            elif rand == 4:
                obstacles2.append(LargeCactus1(LARGE_CACTUS_LIST))
            elif rand == 5:
                obstacles2.append(Bird1(BIRD_LIST))
            

        for obstacle in obstacles2:
            obstacle.update()  # 障礙物移動
            obstacle.draw(window)  # 更新動畫

            if player.dino_rect.colliderect(obstacle.rect):
                pygame.time.delay(20) # 延遲0.02秒
                menu(True)

            if obstacle.rect.x < -obstacle.rect.width:
                obstacles2.pop()

        pygame.display.update()
        
        clock.tick(60)

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    menu(False)