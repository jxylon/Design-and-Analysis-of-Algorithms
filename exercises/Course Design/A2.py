from turtle import Turtle, Screen
import math

turtle = Turtle()
sc = Screen()


def set_init(x, y, e):
    """
    初始化
    :param x: x坐标
    :param y: y坐标
    :param e: 角度，与x轴正方向
    """
    # 擦去画笔痕迹
    turtle.penup()
    # 回到xy点
    turtle.goto(x, y)
    # 设置朝向
    turtle.setheading(e)
    # 恢复画笔痕迹
    turtle.pendown()


def tree(start_len, e, x, y):
    """
    分形树
    :param start_len: 起始长度
    :param e: 角度
    :param x: x坐标
    :param y: y坐标
    """
    turtle.speed('fastest')
    # 终止长度20
    if (start_len > 10):
        # 设置画笔颜色和宽度
        turtle.color('brown')
        turtle.pensize(4)
        if (start_len < 100):
            turtle.color('red')
            turtle.pensize(2)
        if (start_len < 50):
            turtle.color('green')
            turtle.pensize(2)
        # 初始化
        set_init(x, y, e)
        # 前进长度
        turtle.forward(start_len)
        # 1/3长度
        len13 = start_len / 3
        # 2/3长度
        len23 = start_len / 3 * 2
        # 计算1/3，2/3处的坐标和角度
        msin = int(start_len * math.sin(e / 360 * 2 * math.pi))  # 长度的正弦值
        mcos = int(start_len * math.cos(e / 360 * 2 * math.pi))  # 长度的余弦值
        right_x = int(x + mcos / 3)  # 1/3长度
        right_y = int(y + msin / 3)  # 1/3长度
        left_x = int(x + mcos * 2 / 3)  # 2/3长度
        left_y = int(y + msin * 2 / 3)  # 2/3长度
        right_e = (e - 60) % 360  # 右转30度
        left_e = (e + 60) % 360  # 左转30度
        # 画右边分支
        tree(len23, right_e, right_x, right_y)
        # 画左边分支
        tree(len13, left_e, left_x, left_y)


def main():
    origin_len = 400
    turtle.color('brown')
    turtle.speed(2)
    # 左转90°朝向上方
    turtle.left(90)
    turtle.pensize(4)
    tree(origin_len, 90, 0, -200)
    set_init(0, -200, 120)
    sc.exitonclick()


if __name__ == '__main__':
    main()
