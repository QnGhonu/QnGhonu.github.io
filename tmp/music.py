# - coding: utf-8 -*-
import time
import requests
import json
import os
 
# 设置请求头
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
}
 
# 获取指定歌手的歌曲信息
def get_artist_songs(artist_id):
    """
    发送请求获取指定歌手的歌曲信息
    参数:
    artist_id (str): 歌手的 ID
    返回:
    list or None: 成功则返回歌曲列表，否则返回 None
    """
    url = 'https://music.163.com/api/v1/artist/songs'  # 歌手歌曲信息 API 的 URL
    params = {
        'id': artist_id,  # 歌手 ID
        'offset': 0,  # 偏移量
        'total': True,  # 是否获取全部歌曲信息
        'limit': 1000  # 获取歌曲数量
    }
    try:
        response = requests.get(url, headers=headers, params=params)  # 发送 GET 请求
        response.raise_for_status()  # 如果响应状态码不是 200，抛出异常
        result = json.loads(response.text)  # 将响应的文本内容转为 JSON 格式
        songs = result['songs']  # 获取歌曲列表
        return songs
    except requests.exceptions.RequestException as e:
        print('请求出错:', e)  # 打印请求错误信息
        return None
 
# 下载歌曲
def download_song(song_name, song_url, save_dir):
    """
    下载指定歌曲并保存到指定目录
    参数:
    song_name (str): 歌曲名称
    song_url (str): 歌曲的下载 URL
    save_dir (str): 保存歌曲的目录
    """
    if not os.path.exists(save_dir):  # 如果保存目录不存在，则创建目录
        os.makedirs(save_dir)
    save_path = os.path.join(save_dir, '{}.mp3'.format(song_name))  # 拼接保存路径和文件名
    if os.path.exists(save_path):  # 如果文件已存在，则跳过下载
        print('{} 已存在，跳过下载！'.format(song_name))
        return
    try:
        response = requests.get(song_url, headers=headers)  # 发送 GET 请求
        response.raise_for_status()  # 如果响应状态码不是 200，抛出异常
        with open(save_path, 'wb') as f:  # 以二进制写入模式打开文件
            f.write(response.content)
        print('{} 下载完成！'.format(song_name))  # 打印下载完成信息
    except requests.exceptions.RequestException as e:
        print('{} 下载失败！'.format(song_name))  # 打印下载失败信息
 
# 获取歌曲名称和播放链接
def get_song_info(song):
    """
    从歌曲数据中提取歌曲名称和播放链接
    参数:
    song (dict): 包含歌曲信息的字典
    返回:
    tuple: 歌曲名称和播放链接的元组
    """
    song_name = song['name']  # 歌曲名称
    song_id = song['id']  # 歌曲 ID
    url = f'http://music.163.com/song/media/outer/url?id={song_id}'  # 歌曲播放链接
    return song_name, url
 
# 下载一个歌手的所有歌曲
def artist(artist_id):
    # artist_id # 歌手 ID，这里以陈奕迅为例，歌手 ID 可以在网易云音乐上搜索歌手，进入歌手的主页，查看 URL 中的 ID 参数即为该歌手的 ID
    num_songs = 100000  # 下载歌曲数量
    songs = get_artist_songs(artist_id)  # 获取歌手的歌曲信息
    if songs:
        save_dir = str(artist_id)  # 保存目录
        for i, song in enumerate(songs):
            if i >= num_songs:
                break
            song_name, song_url = get_song_info(song)  # 获取歌曲名称和播放链接
            download_song(song_name, song_url, save_dir)  # 下载歌曲
    else:
        print('获取歌曲信息失败！')  # 如果获取歌曲信息失败

# 主函数
if __name__ == '__main__':
    artists = [
        1030001, # 周深
        2116, # 陈奕迅
        7763, # 邓紫棋
        14100246, # Laur
        1087239, # Team-Gericrm
        12073277, # Sakuzyo
        999238, # 山茶花
        12001189, # Daily天利
        159692, # 初音ミク
        12007207, # LeaF
        12063047, # A-39
        54911645, # 茶鸣拾贰律
        14077324, # 黄霄雲
        5538, # 汪苏泷
        12487174, # HOYO-MiX
        6472, # 张杰
        6452, # 周杰伦
        3684, # 林俊杰
        12138269, # 毛不易
    ]
    for i in artists:
        time.sleep(0.1)
        try:
            artist(i) # 下载 Id 为 i 的歌手的歌曲
        except Exception:
            print("歌手 {} 的所有歌曲下载完成！".format(i))
    print('所有歌曲下载完成！')