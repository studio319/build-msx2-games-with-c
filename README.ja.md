# C言語で作るMSX2ゲーム — サンプルソースコード

**MSXglで学ぶレトロゲームプログラミング**

**原題：C언어로 만드는 MSX2 게임**  
**Studio 319**

[한국어](README.md) | [English](README.en.md) | **日本語**

このリポジトリでは、書籍『C언어로 만드는 MSX2 게임』（英語タイトル：*Build MSX2 Games with C*）の**実習用ソースコードとビルド済みのMSX2用ROMファイル**を公開しています。サンプルは書籍に掲載されている順序で並べています。ソースコードを変更して自分でビルドすることも、用意されたROMをMSX2エミュレーターで実行することもできます。

## はじめに

1. リポジトリ上部の **Code → Download ZIP** を選び、サンプル一式をダウンロードして展開します。公開リポジトリのダウンロードにGitHubアカウントは必要ありません。
2. 下の**サンプル一覧**から書籍の節番号を探し、該当するプロジェクトフォルダを開きます。
3. すぐに実行する場合は、各プロジェクトの `out` フォルダにある `.rom` ファイルをopenMSXなどのMSX2エミュレーターで開きます。
4. 自分でビルドする場合は、まず書籍の第2章に従って **MSXglやSDCCなどの開発環境**を準備します。Windowsでは、サンプルフォルダの `build.bat` を実行します。

### プロジェクトフォルダの主なファイル

```text
ch03/5/draw_point/
├── template.c        # C言語のソースコード
├── project_config.js # ビルド設定
├── msxgl_config.h    # MSXglの設定
├── build.bat         # Windows用ビルドスクリプト
├── build.sh          # シェル用ビルドスクリプト
├── out/
│   └── template.rom  # ビルド済みROM
└── emul/
    └── rom/
        └── template.rom  # エミュレーター用ROMのコピー
```

> ファイル構成は開発段階によって異なります。第4章と第5章では、`block_data.c`、`board.c`、`player.c`、`enemy.c` など、機能ごとにソースファイルを分割したプロジェクトもあります。第5章のビルド済みROMのファイル名は主に `vertical_shooter.rom` です。

## サンプル一覧

**以下の表は、GitHubのフォルダ名の並び順ではなく、書籍の学習順序**に従っています。同じ節に複数のサンプルがある場合は、表の順序どおりに確認してください。リンクから各プロジェクトフォルダまたはROMファイルを開けます。

### 第3章 · MSX2プログラミングの基礎

| 本書の節 | 順序 | サンプルフォルダ | 実行ROM |
|---|:---:|---|---|
| 3-5 SCREEN 5で図形を描く | 1 | [`draw_point`](ch03/5/draw_point/) — 点を描く | [ROM](ch03/5/draw_point/out/template.rom) |
| ↳ 同じ節 | 2 | [`draw_line`](ch03/5/draw_line/) — 線を描く | [ROM](ch03/5/draw_line/out/template.rom) |
| ↳ 同じ節 | 3 | [`draw_box`](ch03/5/draw_box/) — 四角形を描く | [ROM](ch03/5/draw_box/out/template.rom) |
| ↳ 同じ節 | 4 | [`draw_fillbox`](ch03/5/draw_fillbox/) — 塗りつぶした四角形を描く | [ROM](ch03/5/draw_fillbox/out/template.rom) |
| ↳ 同じ節 | 5 | [`draw_circle`](ch03/5/draw_circle/) — 円を描く | [ROM](ch03/5/draw_circle/out/template.rom) |
| ↳ 同じ節 | 6 | [`draw_example`](ch03/5/draw_example/) — 基本図形の総合サンプル | [ROM](ch03/5/draw_example/out/template.rom) |
| 3-6 キーボードとジョイスティックの入力 | 1 | [`keyboard_input`](ch03/6/keyboard_input/) — キーボード入力を読み取る | [ROM](ch03/6/keyboard_input/out/template.rom) |
| 3-7 ゲームループとオブジェクトの移動 | 1 | [`move_box`](ch03/7/move_box/) — 四角形を動かす | [ROM](ch03/7/move_box/out/template.rom) |
| ↳ 同じ節 | 2 | [`move_box2`](ch03/7/move_box2/) — 移動後の四角形の軌跡を消す | [ROM](ch03/7/move_box2/out/template.rom) |
| ↳ 同じ節 | 3 | [`move_box3`](ch03/7/move_box3/) — 画面の範囲内に移動を制限する | [ROM](ch03/7/move_box3/out/template.rom) |
| 3-8 スプライト | 1 | [`sprite`](ch03/8/sprite/) — スプライトを表示する | [ROM](ch03/8/sprite/out/template.rom) |
| ↳ 同じ節 | 2 | [`move_sprite`](ch03/8/move_sprite/) — スプライトを動かす | [ROM](ch03/8/move_sprite/out/template.rom) |
| ↳ 同じ節 | 3 | [`move_sprite2`](ch03/8/move_sprite2/) — 背景上でスプライトを動かす | [ROM](ch03/8/move_sprite2/out/template.rom) |
| 3-9 PSGで音を鳴らす | 1 | [`psg`](ch03/9/psg/) — PSGのトーンを鳴らす | [ROM](ch03/9/psg/out/template.rom) |
| ↳ 同じ節 | 2 | [`noise`](ch03/9/noise/) — PSGのノイズを鳴らす | [ROM](ch03/9/noise/out/template.rom) |
| ↳ 同じ節 | 3 | [`music`](ch03/9/music/) — メロディーを演奏する | [ROM](ch03/9/music/out/template.rom) |
| 3-10 配列で複数のデータを管理する | 1 | [`music_array`](ch03/10/music_array/) — 配列でメロディーを管理する | [ROM](ch03/10/music_array/out/template.rom) |
| ↳ 同じ節 | 2 | [`music_array2`](ch03/10/music_array2/) — 2次元配列でメロディーを管理する | [ROM](ch03/10/music_array2/out/template.rom) |
| 3-11 構造体で複数の情報をまとめて管理する | 1 | [`move_sprite3`](ch03/11/move_sprite3/) — 構造体を使ってスプライトを動かす | [ROM](ch03/11/move_sprite3/out/template.rom) |

### 第4章 · 落ち物パズルゲームを作る

| 本書の節 | 順序 | サンプルフォルダ | 実行ROM |
|---|:---:|---|---|
| 4-2 10×20のゲーム盤を作る | 1 | [`gameboard`](ch04/2/gameboard/) — 10×20のゲーム盤を作る | [ROM](ch04/2/gameboard/out/template.rom) |
| 4-3 ブロックの形をデータで表現する | 1 | [`draw_block`](ch04/3/draw_block/) — ブロック形状のデータ定義と描画 | [ROM](ch04/3/draw_block/out/template.rom) |
| 4-4 ブロックを左右に動かす | 1 | [`move_block`](ch04/4/move_block/) — ブロックを左右に動かす | [ROM](ch04/4/move_block/out/template.rom) |
| 4-5 ブロックを自動的に落下させる | 1 | [`fall_block`](ch04/5/fall_block/) — ブロックを自動的に落下させる | [ROM](ch04/5/fall_block/out/template.rom) |
| 4-6 ブロックを固定して次のブロックを生成する | 1 | [`stack_blocks`](ch04/6/stack_blocks/) — ブロックの固定と次のブロックの生成 | [ROM](ch04/6/stack_blocks/out/template.rom) |
| 4-7 さまざまなブロックを作る | 1 | [`multiple_shapes`](ch04/7/multiple_shapes/) — 複数のブロック形状を使う | [ROM](ch04/7/multiple_shapes/out/template.rom) |
| ↳ 同じ節 | 2 | [`random_shapes`](ch04/7/random_shapes/) — ブロック形状をランダムに選ぶ | [ROM](ch04/7/random_shapes/out/template.rom) |
| 4-8 ブロックを回転させる | 1 | [`rotate_shapes`](ch04/8/rotate_shapes/) — ブロックを回転させる | [ROM](ch04/8/rotate_shapes/out/template.rom) |
| 4-9 そろったラインを消す | 1 | [`clear_lines`](ch04/9/clear_lines/) — そろったラインを消す | [ROM](ch04/9/clear_lines/out/template.rom) |
| 4-10 ゲームオーバーを処理する | 1 | [`gameover`](ch04/10/gameover/) — ゲームオーバーを処理する | [ROM](ch04/10/gameover/out/template.rom) |
| 4-11 下矢印キーでブロックを素早く下げる | 1 | [`keyboard_drop`](ch04/11/keyboard_drop/) — 下矢印キーの入力を処理する | [ROM](ch04/11/keyboard_drop/out/template.rom) |
| 4-12 ゲームに難易度を追加する | 1 | [`level_up`](ch04/12/level_up/) — レベルと落下速度を実装する | [ROM](ch04/12/level_up/out/template.rom) |
| 4-13 シンプルなUIを追加する | 1 | [`ui`](ch04/13/ui/) — スコアやレベルなどのUIを表示する | [ROM](ch04/13/ui/out/template.rom) |
| 4-14 ソースコードを整理する | 1 | [`code_refactoring`](ch04/14/code_refactoring/) — ソースファイルを分割して整理する | [ROM](ch04/14/code_refactoring/out/template.rom) |
| 4-15 効果音を追加する | 1 | [`sfx`](ch04/15/sfx/) — 効果音を追加する | [ROM](ch04/15/sfx/out/template.rom) |
| 4-16 ゲームを調整して完成させる | 1 | [`falling_blocks`](ch04/16/falling_blocks/) — 完成した落ち物パズルゲーム | [ROM](ch04/16/falling_blocks/out/template.rom) |

### 第5章 · 縦スクロールシューティングゲームを作る

| 本書の節 | 順序 | サンプルフォルダ | 実行ROM |
|---|:---:|---|---|
| 5-2 プレイヤーを動かす | 1 | [`player_sprite`](ch05/2/player_sprite/) — プレイヤーのスプライトを表示する | [ROM](ch05/2/player_sprite/out/vertical_shooter.rom) |
| ↳ 同じ節 | 2 | [`move_player`](ch05/2/move_player/) — プレイヤーを動かす | [ROM](ch05/2/move_player/out/vertical_shooter.rom) |
| ↳ 同じ節 | 3 | [`move_player_in_range`](ch05/2/move_player_in_range/) — プレイヤーの移動範囲を制限する | [ROM](ch05/2/move_player_in_range/out/vertical_shooter.rom) |
| 5-3 弾を発射する | 1 | [`bullet_fire`](ch05/3/bullet_fire/) — 弾を発射する | [ROM](ch05/3/bullet_fire/out/vertical_shooter.rom) |
| 5-4 複数の弾を管理する | 1 | [`multiple_bullets`](ch05/4/multiple_bullets/) — 複数の弾を管理する | [ROM](ch05/4/multiple_bullets/out/vertical_shooter.rom) |
| 5-5 敵を出現させる | 1 | [`spawn_enemies`](ch05/5/spawn_enemies/) — 敵を出現させる | [ROM](ch05/5/spawn_enemies/out/vertical_shooter.rom) |
| 5-6 弾と敵の当たり判定を実装する | 1 | [`collision_enemy_bullet`](ch05/6/collision_enemy_bullet/) — プレイヤーの弾と敵の当たり判定 | [ROM](ch05/6/collision_enemy_bullet/out/vertical_shooter.rom) |
| 5-7 プレイヤーと敵の衝突を処理する | 1 | [`collision_enemy_player`](ch05/7/collision_enemy_player/) — プレイヤーと敵の当たり判定 | [ROM](ch05/7/collision_enemy_player/out/vertical_shooter.rom) |
| 5-8 スクロールする背景を追加する | 1 | [`bg_scroll_1(wrong)`](ch05/8/bg_scroll_1%28wrong%29/) — 背景スクロールの問題例 | [ROM](ch05/8/bg_scroll_1%28wrong%29/out/vertical_shooter.rom) |
| ↳ 同じ節 | 2 | [`bg_scroll_2(fixed)`](ch05/8/bg_scroll_2%28fixed%29/) — 背景スクロールの修正版 | [ROM](ch05/8/bg_scroll_2%28fixed%29/out/vertical_shooter.rom) |
| 5-9 スプライトの位置ずれを修正する | 1 | [`scroll_sprite`](ch05/9/scroll_sprite/) — スクロール中のスプライト座標を補正する | [ROM](ch05/9/scroll_sprite/out/vertical_shooter.rom) |
| 5-10 ゲームの処理速度を最適化する | 1 | [`profile`](ch05/10/profile/) — 処理速度を測定して最適化する | [ROM](ch05/10/profile/out/vertical_shooter.rom) |
| 5-11 さまざまな敵を作る | 1 | [`various_enemies`](ch05/11/various_enemies/) — さまざまな種類の敵を追加する | [ROM](ch05/11/various_enemies/out/vertical_shooter.rom) |
| ↳ 同じ節 | 2 | [`enemy_bullet`](ch05/11/enemy_bullet/) — 敵が弾を発射する | [ROM](ch05/11/enemy_bullet/out/vertical_shooter.rom) |
| 5-12 爆発エフェクトを作る | 1 | [`vertical_shooter`](ch05/12/vertical_shooter/) — 爆発エフェクトを追加する | [ROM](ch05/12/vertical_shooter/out/vertical_shooter.rom) |
| 5-13 タイトル画面とゲームUIを完成させる | 1 | [`ui`](ch05/13/ui/) — タイトル画面とゲームUIを追加する | [ROM](ch05/13/ui/out/vertical_shooter.rom) |
| 5-14 ゲームにBGMを追加する | 1 | [`bgm`](ch05/14/bgm/) — BGMを追加する | [ROM](ch05/14/bgm/out/vertical_shooter.rom) |
| 5-15 ゲームに効果音を追加する | 1 | [`sfx`](ch05/15/sfx/) — 効果音を追加する | [ROM](ch05/15/sfx/out/vertical_shooter.rom) |

## ビルドと実行

### ROMをそのまま実行する

- 各プロジェクトの `out` フォルダから `.rom` ファイルをダウンロードし、openMSXなどのMSX2エミュレーターで実行します。
- 一部のプロジェクトには `emul/rom` にもROMファイルがあります。混乱を避けるため、この案内のROMリンクはすべて **`out` フォルダ内のファイル**を参照します。

### ソースコードをビルドする（Windows）

1. 書籍の**第2章**に従い、MSXglの開発環境を設定します。
2. 環境変数 `MSXGL_PATH` がMSXglのインストールフォルダを指していることを確認します。
3. ビルドしたいプロジェクトのフォルダで `build.bat` を実行します。
4. ビルド完了後、プロジェクトの `out` フォルダに生成された `.rom` ファイルを確認します。

```bat
build.bat
```

> **パスに関する注意：** 使用するMSXglビルドツールのバージョンによっては、プロジェクトのパスに**スペースや韓国語の文字**が含まれる場合、またはMSXglとプロジェクトが**異なるドライブ**にある場合、ビルドに失敗することがあります。その場合は、両方のフォルダを同じドライブ上のスペースを含まない英数字のパスに配置して、再度ビルドしてください。詳しい設定方法は書籍の第2章を参照してください。

## 補足事項

- 第1章と第2章では、基礎知識と開発環境の構築を扱います。独立した実習プロジェクトは**第3章から**収録しています。
- 第4章と第5章のサンプルは、ゲームを段階的に拡張していくものです。各プロジェクトは、それぞれの節の学習段階に対応しています。
- `out` フォルダのROMは実行用のビルド成果物です。ソースコードを変更した場合は、再ビルドして新しいROMを生成できます。
- このリポジトリは学習用のサンプルを提供しています。**別途ライセンスが指定されていない公開リポジトリであっても、自由な再利用・再配布が無制限に認められるわけではありません。** 利用条件は、著作権者の案内または別途提供されるライセンスに従ってください。

---

**Studio 319** · 『C언어로 만드는 MSX2 게임』のサンプル資料
