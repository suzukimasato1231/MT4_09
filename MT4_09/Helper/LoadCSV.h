#pragma once

#define MAP_WIDTH (100) //横の最大枚数
#define MAP_HEIGHT (20)  //縦の最大枚数

/// <summary>
/// CSVファイルの読み込み
/// </summary>
/// <param name="map"> 読み込んだCSVファイルの保存先 </param>
/// <param name="FilePath"> CSVファイルのパス </param>
/// <param name="LoadStopNumber"> ここに指定された値がヒットすると読み込みを終了する </param>
/// <returns> 0以外で失敗、0で成功 </returns>
int LoadCSV(int map[MAP_HEIGHT][MAP_WIDTH], const char *FilePath, int LoadStopNumber = -1);

/// <summary>
/// CSVファイルの読み込み(1次元配列)
/// </summary>
/// <param name="mapArray"> 読み込んだCSVファイルの保存先 </param>
/// <param name="FilePath"> CSVファイルのパス </param>
/// <param name="LoadStopNumber"> ここに指定された値がヒットすると読み込みを終了する </param>
/// <returns> 0以外で失敗、0で成功 </returns>
int LoadCSV1D(int *mapArray, const size_t &mapSize, const char *FilePath, int LoadStopNumber = -1);
