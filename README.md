# C언어로 만드는 MSX2 게임 — 예제 소스코드

**MSXgl로 배우는 레트로 게임 프로그래밍**

**Build MSX2 Games with C**  
**Studio 319**

이 저장소는 《C언어로 만드는 MSX2 게임》의 **실습 예제 소스코드와 빌드된 MSX2용 ROM 파일**을 제공한다. 책에서 설명하는 순서대로 예제를 찾아볼 수 있으며, 코드를 직접 수정해 빌드하거나 준비된 ROM을 에뮬레이터에서 실행할 수 있다.

**한국어** | [English](README.en.md) | [日本語](README.ja.md)

## 빠른 시작

1. 저장소 상단의 **Code → Download ZIP**을 클릭해 전체 예제를 내려받은 뒤 압축을 푼다. GitHub 계정 없이도 공개 저장소를 다운로드할 수 있다.
2. 아래 **예제 목록**에서 책의 절 번호를 찾아 원하는 프로젝트 폴더를 연다.
3. 바로 실행하려면 해당 폴더의 `out`에 있는 `.rom` 파일을 MSX2 에뮬레이터(예: openMSX)에서 연다.
4. 직접 빌드하려면 먼저 책의 2장에 따라 **MSXgl 개발 환경과 SDCC** 등을 준비하고, Windows에서 예제 폴더의 `build.bat`를 실행한다.

### 프로젝트 폴더의 주요 파일

```text
ch03/5/draw_point/
├── template.c        # C 소스코드
├── project_config.js # 빌드 설정
├── msxgl_config.h    # MSXgl 설정
├── build.bat         # Windows 빌드 스크립트
├── build.sh          # 셸용 빌드 스크립트
├── out/
│   └── template.rom  # 빌드 결과 ROM
└── emul/
    └── rom/
        └── template.rom  # 에뮬레이터용 복사본
```

> 각 예제의 파일 구성은 개발 단계에 따라 달라진다. 4장과 5장에는 `block_data.c`, `board.c`, `player.c`, `enemy.c`처럼 기능별로 분리한 소스 파일도 있다. 5장의 빌드 ROM 파일명은 주로 `vertical_shooter.rom`이다.

## 예제 목록

**표는 GitHub의 폴더명 정렬 순서가 아니라 교재의 실습 진행 순서**를 따른다. 같은 절에 예제가 여러 개라면 표의 순서에 따라 차례로 확인하면 된다. 링크를 클릭하면 해당 예제 폴더나 ROM 파일로 이동한다.

### 3장 · MSX2 프로그래밍 기초

| 책의 절 | 순서 | 예제 폴더 | 실행 ROM |
|---|:---:|---|---|
| 3-5 SCREEN 5에서 그림 그리기 | 1 | [`draw_point`](ch03/5/draw_point/) — 점 그리기 | [ROM](ch03/5/draw_point/out/template.rom) |
| ↳ 같은 절 | 2 | [`draw_line`](ch03/5/draw_line/) — 선 그리기 | [ROM](ch03/5/draw_line/out/template.rom) |
| ↳ 같은 절 | 3 | [`draw_box`](ch03/5/draw_box/) — 사각형 그리기 | [ROM](ch03/5/draw_box/out/template.rom) |
| ↳ 같은 절 | 4 | [`draw_fillbox`](ch03/5/draw_fillbox/) — 채워진 사각형 그리기 | [ROM](ch03/5/draw_fillbox/out/template.rom) |
| ↳ 같은 절 | 5 | [`draw_circle`](ch03/5/draw_circle/) — 원 그리기 | [ROM](ch03/5/draw_circle/out/template.rom) |
| ↳ 같은 절 | 6 | [`draw_example`](ch03/5/draw_example/) — 기본 도형 종합 예제 | [ROM](ch03/5/draw_example/out/template.rom) |
| 3-6 키보드와 조이스틱 입력 | 1 | [`keyboard_input`](ch03/6/keyboard_input/) — 키보드 입력 | [ROM](ch03/6/keyboard_input/out/template.rom) |
| 3-7 게임 루프와 오브젝트 움직이기 | 1 | [`move_box`](ch03/7/move_box/) — 사각형 이동 | [ROM](ch03/7/move_box/out/template.rom) |
| ↳ 같은 절 | 2 | [`move_box2`](ch03/7/move_box2/) — 이동한 사각형의 흔적 지우기 | [ROM](ch03/7/move_box2/out/template.rom) |
| ↳ 같은 절 | 3 | [`move_box3`](ch03/7/move_box3/) — 화면 밖으로 나가지 않게 이동 범위 제한 | [ROM](ch03/7/move_box3/out/template.rom) |
| 3-8 스프라이트 | 1 | [`sprite`](ch03/8/sprite/) — 스프라이트 표시 | [ROM](ch03/8/sprite/out/template.rom) |
| ↳ 같은 절 | 2 | [`move_sprite`](ch03/8/move_sprite/) — 스프라이트 이동 | [ROM](ch03/8/move_sprite/out/template.rom) |
| ↳ 같은 절 | 3 | [`move_sprite2`](ch03/8/move_sprite2/) — 배경 위에서 스프라이트 이동 | [ROM](ch03/8/move_sprite2/out/template.rom) |
| 3-9 PSG로 소리 내기 | 1 | [`psg`](ch03/9/psg/) — PSG 톤 출력 | [ROM](ch03/9/psg/out/template.rom) |
| ↳ 같은 절 | 2 | [`noise`](ch03/9/noise/) — PSG 노이즈 출력 | [ROM](ch03/9/noise/out/template.rom) |
| ↳ 같은 절 | 3 | [`music`](ch03/9/music/) — 멜로디 연주 | [ROM](ch03/9/music/out/template.rom) |
| 3-10 배열로 여러 데이터 관리하기 | 1 | [`music_array`](ch03/10/music_array/) — 배열로 멜로디 관리 | [ROM](ch03/10/music_array/out/template.rom) |
| ↳ 같은 절 | 2 | [`music_array2`](ch03/10/music_array2/) — 2차원 배열로 멜로디 관리 | [ROM](ch03/10/music_array2/out/template.rom) |
| 3-11 구조체로 여러 정보를 묶어 관리하기 | 1 | [`move_sprite3`](ch03/11/move_sprite3/) — 구조체를 이용한 스프라이트 이동 | [ROM](ch03/11/move_sprite3/out/template.rom) |

### 4장 · 낙하 블록 퍼즐 게임 만들기

| 책의 절 | 순서 | 예제 폴더 | 실행 ROM |
|---|:---:|---|---|
| 4-2 10×20 게임판 만들기 | 1 | [`gameboard`](ch04/2/gameboard/) — 10×20 게임판 만들기 | [ROM](ch04/2/gameboard/out/template.rom) |
| 4-3 블록 모양을 데이터로 만들기 | 1 | [`draw_block`](ch04/3/draw_block/) — 블록 모양 데이터와 그리기 | [ROM](ch04/3/draw_block/out/template.rom) |
| 4-4 블록을 좌우로 움직이기 | 1 | [`move_block`](ch04/4/move_block/) — 블록 좌우 이동 | [ROM](ch04/4/move_block/out/template.rom) |
| 4-5 블록을 자동으로 떨어뜨리기 | 1 | [`fall_block`](ch04/5/fall_block/) — 블록 자동 낙하 | [ROM](ch04/5/fall_block/out/template.rom) |
| 4-6 블록을 쌓고 다음 블록을 만들자 | 1 | [`stack_blocks`](ch04/6/stack_blocks/) — 블록 고정과 다음 블록 생성 | [ROM](ch04/6/stack_blocks/out/template.rom) |
| 4-7 다양한 블록을 만들자 | 1 | [`multiple_shapes`](ch04/7/multiple_shapes/) — 여러 블록 모양 | [ROM](ch04/7/multiple_shapes/out/template.rom) |
| ↳ 같은 절 | 2 | [`random_shapes`](ch04/7/random_shapes/) — 무작위 블록 선택 | [ROM](ch04/7/random_shapes/out/template.rom) |
| 4-8 블록을 회전시키자 | 1 | [`rotate_shapes`](ch04/8/rotate_shapes/) — 블록 회전 | [ROM](ch04/8/rotate_shapes/out/template.rom) |
| 4-9 완성된 줄을 지우자 | 1 | [`clear_lines`](ch04/9/clear_lines/) — 완성된 줄 지우기 | [ROM](ch04/9/clear_lines/out/template.rom) |
| 4-10 게임 오버를 처리하자 | 1 | [`gameover`](ch04/10/gameover/) — 게임 오버 처리 | [ROM](ch04/10/gameover/out/template.rom) |
| 4-11 아래 방향키로 블록을 빠르게 내리자 | 1 | [`keyboard_drop`](ch04/11/keyboard_drop/) — 아래 방향키 입력 처리 | [ROM](ch04/11/keyboard_drop/out/template.rom) |
| 4-12 게임에 난이도를 추가하자 | 1 | [`level_up`](ch04/12/level_up/) — 레벨과 낙하 속도 | [ROM](ch04/12/level_up/out/template.rom) |
| 4-13 간단한 UI를 추가하자 | 1 | [`ui`](ch04/13/ui/) — 점수·레벨 등 UI 표시 | [ROM](ch04/13/ui/out/template.rom) |
| 4-14 소스 코드를 정리하자 | 1 | [`code_refactoring`](ch04/14/code_refactoring/) — 소스 코드 파일 분리·정리 | [ROM](ch04/14/code_refactoring/out/template.rom) |
| 4-15 효과음을 추가하자 | 1 | [`sfx`](ch04/15/sfx/) — 효과음 추가 | [ROM](ch04/15/sfx/out/template.rom) |
| 4-16 게임을 다듬고 완성하자 | 1 | [`falling_blocks`](ch04/16/falling_blocks/) — 낙하 블록 퍼즐 완성 | [ROM](ch04/16/falling_blocks/out/template.rom) |

### 5장 · 종스크롤 슈팅 게임 만들기

| 책의 절 | 순서 | 예제 폴더 | 실행 ROM |
|---|:---:|---|---|
| 5-2 플레이어를 움직이게 하자 | 1 | [`player_sprite`](ch05/2/player_sprite/) — 플레이어 스프라이트 표시 | [ROM](ch05/2/player_sprite/out/vertical_shooter.rom) |
| ↳ 같은 절 | 2 | [`move_player`](ch05/2/move_player/) — 플레이어 이동 | [ROM](ch05/2/move_player/out/vertical_shooter.rom) |
| ↳ 같은 절 | 3 | [`move_player_in_range`](ch05/2/move_player_in_range/) — 플레이어 이동 범위 제한 | [ROM](ch05/2/move_player_in_range/out/vertical_shooter.rom) |
| 5-3 총알을 발사하자 | 1 | [`bullet_fire`](ch05/3/bullet_fire/) — 총알 발사 | [ROM](ch05/3/bullet_fire/out/vertical_shooter.rom) |
| 5-4 여러 총알을 관리하자 | 1 | [`multiple_bullets`](ch05/4/multiple_bullets/) — 여러 총알 관리 | [ROM](ch05/4/multiple_bullets/out/vertical_shooter.rom) |
| 5-5 적을 등장시키자 | 1 | [`spawn_enemies`](ch05/5/spawn_enemies/) — 적 등장 | [ROM](ch05/5/spawn_enemies/out/vertical_shooter.rom) |
| 5-6 총알과 적의 충돌을 검사하자 | 1 | [`collision_enemy_bullet`](ch05/6/collision_enemy_bullet/) — 플레이어 총알과 적의 충돌 | [ROM](ch05/6/collision_enemy_bullet/out/vertical_shooter.rom) |
| 5-7 플레이어와 적의 충돌을 처리하자 | 1 | [`collision_enemy_player`](ch05/7/collision_enemy_player/) — 플레이어와 적의 충돌 | [ROM](ch05/7/collision_enemy_player/out/vertical_shooter.rom) |
| 5-8 스크롤 되는 배경을 추가하자 | 1 | [`bg_scroll_1(wrong)`](ch05/8/bg_scroll_1%28wrong%29/) — 배경 스크롤 문제 사례 | [ROM](ch05/8/bg_scroll_1%28wrong%29/out/vertical_shooter.rom) |
| ↳ 같은 절 | 2 | [`bg_scroll_2(fixed)`](ch05/8/bg_scroll_2%28fixed%29/) — 배경 스크롤 수정 사례 | [ROM](ch05/8/bg_scroll_2%28fixed%29/out/vertical_shooter.rom) |
| 5-9 스프라이트의 위치 오차를 해결하자 | 1 | [`scroll_sprite`](ch05/9/scroll_sprite/) — 스크롤 중 스프라이트 좌표 보정 | [ROM](ch05/9/scroll_sprite/out/vertical_shooter.rom) |
| 5-10 게임의 처리 속도를 최적화하자 | 1 | [`profile`](ch05/10/profile/) — 처리 속도 확인 및 최적화 | [ROM](ch05/10/profile/out/vertical_shooter.rom) |
| 5-11 다양한 적을 만들자 | 1 | [`various_enemies`](ch05/11/various_enemies/) — 여러 종류의 적 | [ROM](ch05/11/various_enemies/out/vertical_shooter.rom) |
| ↳ 같은 절 | 2 | [`enemy_bullet`](ch05/11/enemy_bullet/) — 적의 총알 발사 | [ROM](ch05/11/enemy_bullet/out/vertical_shooter.rom) |
| 5-12 폭발 효과를 만들자 | 1 | [`vertical_shooter`](ch05/12/vertical_shooter/) — 폭발 효과 추가 | [ROM](ch05/12/vertical_shooter/out/vertical_shooter.rom) |
| 5-13 타이틀과 게임 UI를 완성하자 | 1 | [`ui`](ch05/13/ui/) — 타이틀과 게임 UI | [ROM](ch05/13/ui/out/vertical_shooter.rom) |
| 5-14 게임에 배경음악을 추가하자 | 1 | [`bgm`](ch05/14/bgm/) — 배경음악 추가 | [ROM](ch05/14/bgm/out/vertical_shooter.rom) |
| 5-15 게임에 효과음을 추가하자 | 1 | [`sfx`](ch05/15/sfx/) — 효과음 추가 | [ROM](ch05/15/sfx/out/vertical_shooter.rom) |

## 빌드 및 실행 안내

### ROM을 바로 실행하기

- 각 프로젝트의 `out` 폴더에서 `.rom` 파일을 내려받아 openMSX 등의 MSX2 에뮬레이터에서 실행하면 된다.
- 일부 프로젝트의 `emul/rom`에도 ROM 파일이 있다. 이 저장소에서 안내하는 실행 파일 링크는 혼동을 줄이기 위해 **`out` 폴더의 ROM**을 기준으로 한다.

### 소스코드를 빌드하기 (Windows)

1. 먼저 책의 **2장**에 설명한 방식으로 MSXgl 빌드 환경을 구성한다.
2. PC에서 `MSXGL_PATH` 환경변수가 MSXgl 설치 폴더를 가리키는지 확인한다.
3. 빌드하려는 예제 폴더에서 `build.bat`를 실행한다.
4. 빌드가 끝나면 해당 프로젝트의 `out` 폴더에서 생성된 `.rom` 파일을 확인한다.

```bat
build.bat
```

> **경로 관련 주의:** 사용 중인 MSXgl 빌드 도구 버전에 따라 프로젝트 경로의 **공백·한글** 또는 MSXgl과 예제 프로젝트가 **서로 다른 드라이브**에 있을 때 빌드 오류가 발생할 수 있다. 문제가 발생하면 두 폴더를 같은 드라이브의 공백 없는 영문 경로에 배치한 뒤 다시 빌드한다. 세부 설치·빌드 과정은 교재의 2장을 참고한다.

## 참고 사항

- 1~2장은 개념 설명과 개발환경 설치를 다루므로, 이 저장소의 독립적인 실습 프로젝트는 **3장부터** 제공한다.
- 4장과 5장의 예제는 게임을 단계별로 확장한 버전이다. 각 예제는 해당 절의 학습 단계에 맞춰 분리되어 있다.
- `out`에 있는 ROM은 실행용 결과물이며, 코드를 변경한 뒤에는 다시 빌드하여 새 ROM을 만들 수 있다.
- 이 저장소는 학습용 예제 파일을 제공한다. **별도 라이선스가 없는 상태에서 공개 저장소라는 이유만으로 무제한 재사용·재배포 권한이 주어지는 것은 아니다.** 구체적인 이용 범위는 저작권자의 안내 또는 별도로 제공되는 라이선스에 따른다.

---

**Studio 319** · 《C언어로 만드는 MSX2 게임》 예제 자료실
