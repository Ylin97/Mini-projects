#! /usr/bin/python

# coding=utf-8


import pygame
from pygame.sprite import Group

from settings import Settings
from ship import Ship
from game_stats import GameStats
from button import Button
from scoreboard import Scoreboard
import game_functions as gf


def run_game():
    # 初始化pygame、设置和屏幕对象
    pygame.init()
    ai_settings = Settings()
    # ai_settings.ship_speed_factor = 1.5
    screen = pygame.display.set_mode(
        (ai_settings.screen_width, ai_settings.screen_height))
    pygame.display.set_caption('Alien Invasion')

    # 创建一艘飞船
    ship = Ship(ai_settings, screen)

    # 创建子弹精灵组
    bullets = Group()

    # 创建外星人精灵组
    aliens = Group()

    # 创建外星人群
    gf.create_fleet(ai_settings, screen, ship, aliens)

    # 创建一个用于存储游戏统计信息的实例，并创建记分牌
    stats = GameStats(ai_settings)
    sb = Scoreboard(ai_settings, screen, stats)

    # 创建Play按钮
    play_button = Button(ai_settings, screen, "Play")

    # 开始游戏循环
    while True:

        # 监视键盘和鼠标
        gf.check_events(ai_settings, screen, stats, sb, play_button, ship,
                        aliens, bullets, stats.high_score)
        if stats.game_active:
            # 更新飞船位置
            ship.update()
            # 更新子弹并删除消失的子弹
            gf.update_bullets(ai_settings, screen, stats, sb, ship, aliens,
                              bullets)
            # 更新外星人
            gf.update_aliens(ai_settings, screen, stats, sb, ship, aliens, bullets)

        # 更新屏幕
        gf.update_screen(ai_settings, screen, stats, sb, ship, aliens, bullets,
                         play_button)


if __name__ == '__main__':
    run_game()
