from turtle import Turtle, Screen
from PIL import Image
import math
import time

turtle = Turtle()
turtle.speed(1000)
sc = Screen()
map = {}
nodes = {'大门', '明德楼', '至善楼', '中门', '第一实验楼', '第二实验楼', '第三实验楼', '4教', '2教', '3教', '1教', '56教', '快乐时间', '图书馆', '菊轩', '竹轩',
         '一食堂', '兰轩', '榕轩', '柏轩', '梅轩', '荷轩', '桂轩', '松轩', '操场'}
place = {
    '大门': (-15, 300),
    '明德楼': (-100, 280),
    '至善楼': (-10, 220),
    '中门': (120, 200),
    '第一实验楼': (-120, 80),
    '第二实验楼': (-180, 150),
    '第三实验楼': (-180, -60),
    '4教': (-130, -100),
    '2教': (-10, -100),
    '3教': (-80, -150),
    '1教': (-80, -100),
    '56教': (60, 130),
    '快乐时间': (30, 70),
    '图书馆': (-10, 40),
    '菊轩': (60, 5),
    '竹轩': (100, -50),
    '一食堂': (50, -90),
    '兰轩': (100, -120),
    '榕轩': (140, -150),
    '松轩': (80, -270),
    '桂轩': (120, -290),
    '荷轩': (20, -280),
    '梅轩': (50, -200),
    '柏轩': (140, -210),
    '操场': (-80, -250)
}


def set_picture():
    # jpg格式设置图片大小，存为gif格式
    img = Image.open('./img/map.jpg')
    (x, y) = img.size
    x_s = 650  # define standard width
    y_s = int(y * x_s / x)  # calc height based on standard width
    out = img.resize((x_s, y_s), Image.ANTIALIAS)  # resize image with high-quality
    out.save('./img/map.gif')


def draw_point(x, y):
    # 各个地点画点
    turtle.color('blue')
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.pensize(4)
    turtle.circle(2)


def draw_line(place1, place2):
    x1 = place[place1][0]
    y1 = place[place1][1]
    x2 = place[place2][0]
    y2 = place[place2][1]
    turtle.penup()
    turtle.goto(x1, y1)
    turtle.pendown()
    turtle.pensize(4)
    turtle.color('red')
    lenth = int(math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2))
    turtle.goto(x2, y2)
    # 长度
    turtle.color('black')
    turtle.pensize(1)
    turtle.penup()
    turtle.goto((x1 + x2) / 2, (y1 + y2) / 2)
    turtle.pendown()
    turtle.write(str(lenth), font=("sans serif", 12, "bold"))
    # 记录
    if (place1 not in map):
        map[place1] = {place2: lenth}
    else:
        map[place1].update({place2: lenth})
    if (place2 not in map):
        map[place2] = {place1: lenth}
    else:
        map[place2].update({place1: lenth})


def simple_line(place1, place2):
    x1 = place[place1][0]
    y1 = place[place1][1]
    x2 = place[place2][0]
    y2 = place[place2][1]
    turtle.penup()
    turtle.goto(x1, y1)
    turtle.pendown()
    turtle.pensize(4)
    turtle.color('yellow')
    turtle.goto(x2, y2)


def draw_all():
    for key, value in place.items():
        draw_point(value[0], value[1])
    draw_line('大门', '明德楼')  # 大门-明德楼
    draw_line('大门', '至善楼')  # 大门-至善楼
    draw_line('明德楼', '第二实验楼')  # 明德楼-第一实验楼
    draw_line('大门', '中门')  # 大门-中门
    draw_line('第三实验楼', '4教')  # 第三实验楼-4教
    draw_line('第三实验楼', '第一实验楼')  # 第三实验楼-第一实验楼
    draw_line('4教', '1教')  # 4教-1教
    draw_line('1教', '2教')  # 1教-2教
    draw_line('1教', '3教')  # 1教-3教
    draw_line('3教', '4教')  # 3教-4教
    draw_line('2教', '3教')  # 2教-3教
    draw_line('2教', '一食堂')  # 2教-1食堂
    draw_line('2教', '图书馆')  # 2教-图书馆
    draw_line('2教', '菊轩')  # 2教-菊轩
    draw_line('图书馆', '菊轩')  # 图书馆-菊轩
    draw_line('图书馆', '快乐时间')  # 图书馆-快乐时间
    draw_line('图书馆', '第一实验楼')  # 图书馆-第一实验楼
    draw_line('第一实验楼', '第二实验楼')  # 第一实验楼-第二实验楼
    draw_line('56教', '快乐时间')  # 56教-快乐时间
    draw_line('56教', '中门')  # 56-中门
    draw_line('竹轩', '菊轩')  # 竹轩-菊轩
    draw_line('竹轩', '兰轩')  # 竹轩-兰轩
    draw_line('竹轩', '一食堂')  # 竹轩-一食堂
    draw_line('兰轩', '一食堂')  # 兰轩-一食堂
    draw_line('兰轩', '榕轩')  # 兰轩-榕轩
    draw_line('榕轩', '柏轩')  # 榕轩-柏轩
    draw_line('柏轩', '桂轩')  # 柏轩-桂轩
    draw_line('柏轩', '梅轩')  # 柏轩-梅轩
    draw_line('桂轩', '松轩')  # 桂轩-松轩
    draw_line('桂轩', '荷轩')  # 桂轩-荷轩
    draw_line('松轩', '荷轩')  # 松轩-荷轩
    draw_line('荷轩', '梅轩')  # 荷轩-梅轩
    draw_line('2教', '梅轩')  # 2教-梅轩
    draw_line('梅轩', '操场')  # 操场-梅轩
    draw_line('荷轩', '操场')  # 操场-荷轩


def shortest_path():
    """
    最短路径，dijsktra算法
    """
    print(nodes)
    print('输入起始地点')
    start = input()
    while (start not in nodes):
        print('地点不在收录中，请重新输入')
        start = input()
    print('输入终点')
    end = input()
    while (end not in nodes):
        print('地点不在收录中，请重新输入')
        end = input()
    # 未访问过的数组，初始化未None
    unvisited = {node: None for node in nodes}
    # 用来记录已经访问过的数组
    visited = {node: [] for node in nodes}
    # 目前到起点的距离
    dis2start = 0
    unvisited[start] = dis2start
    for i in range(len(nodes)):
        for neigh, distance in map[start].items():
            # 被访问过了，跳出本次循环
            if neigh not in unvisited:
                continue
            # 原来到起点的距离加上相邻距离
            newdis = dis2start + distance
            # 如果两个点之间的距离之前是无穷大或者新距离小于原来的距离
            if unvisited[neigh] is None or unvisited[neigh] > newdis:
                # 更新距离
                unvisited[neigh] = newdis
                # 更新路径
                visited[neigh] = [x for x in visited[start]]
                visited[neigh].append(start)
        # 在未访问字典中删除
        del unvisited[start]
        # 如果所有点都访问过，退出
        if not unvisited:
            break
        # 找出字典中不为空的元素
        candidates = [node for node in unvisited.items() if node[1]]
        # 按键值排序，最小元素
        start, dis2start = sorted(candidates, key=lambda x: x[1])[0]
    # 终点加入visited中
    for key, value in visited.items():
        value.append(end)
    # 画出最短路径
    time.sleep(2)
    path_list = visited[end]
    for i in range(len(path_list) - 1):
        simple_line(path_list[i], path_list[i + 1])


def main():
    # set_picture()
    sc.bgpic('./img/map.gif')
    sc.title('地图导航')
    draw_all()
    shortest_path()
    sc.exitonclick()


if __name__ == '__main__':
    main()
