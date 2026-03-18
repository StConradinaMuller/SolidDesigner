<p align="center">
  <img src="Designer/UIResource/TitleBar/brand/light/png/200x56/app_wordmark.png" width="360" alt="SolidDesigner" />
</p>

<p align="center">
  <a href="LICENSE"><img alt="License" src="https://img.shields.io/badge/License-GPLv3-blue.svg" /></a>
  <img alt="C++" src="https://img.shields.io/badge/C%2B%2B-17%2F20-00599C.svg" />
  <img alt="Kernel" src="https://img.shields.io/badge/Kernel-OpenCascade%20(OCCT)-orange" />
  <img alt="UI" src="https://img.shields.io/badge/UI-Qt%20Widgets-41CD52" />
  <img alt="Platform" src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey" />
</p>

<p align="center">
  <b>パラメトリック CAD とシミュレーション駆動設計のための、オープンソースのエンジニアリンググレード・プラットフォーム</b><br/>
  フィーチャベース・モデリング • CAE 対応データモデル • 最適化ファーストのアーキテクチャ
</p>

<p align="center">
  <img src="Docs/media/Breptera_Splash.gif" width="960" alt="SolidDesigner デモプレビュー" />
</p>

<p align="center">
  製品デモプレビュー
</p>

## [English](README.md) | [日本語](README.ja.md) | [Français](README.fr.md) | [Deutsch](README.de.md) | [Español](README.es.md) | [Русский](README.ru.md)

> 目標：ソリッド／サーフェスモデリング、アセンブリ、製図、構造力学、CFD、マルチフィジックス、最適化をサポートし、シミュレーションが設計そのものを駆動できる、プロフェッショナルグレードのシステムを実現することです。

---

## Quick Links

- **JIRA ボード**: https://hananiah.atlassian.net/jira/software/c/projects/AL/boards/3
- **公開 Wiki（GitHub）**: https://github.com/hananiahhsu/SolidDesignerWiki
- **設計 Wiki（Confluence、要アクセス権）**: https://hananiah.atlassian.net/wiki/spaces/~5e2301040f45160ca25e42e3/overview?homepageId=65963

---

## Table of Contents

- [ビジョンとスコープ](#vision--scope)
- [製品概要](#product-overview)
- [同梱内容](#whats-in-the-box)
- [プロジェクト構成とアーキテクチャ](#project-layout--architecture)
- [コア概念](#core-concepts)
- [機能](#capabilities)
- [ロードマップ](#roadmap)
- [ビルドと実行](#build--run)
- [依存関係](#dependencies)
  - [オープンソース構成とライセンス](#open-source-stack--licenses)
- [はじめに](#getting-started)
- [プラグインとスクリプティング](#plugin--scripting)
- [データとファイル形式](#data--file-formats)
- [診断・ログ・QA](#diagnostics-logging--qa)
- [貢献方法](#contributing)
- [ライセンス](#license)
- [謝辞](#acknowledgments)
- [FAQ](#faq)

---

## Vision & Scope

SolidDesigner は、**フルスタックかつエンジニアリング品質**の CAD/CAE プラットフォームを目指します。

- **Parametric CAD**：堅牢なパーツ／アセンブリモデリング、スケッチ／拘束、履歴ベースのフィーチャ、製図。
- **CAE**：**構造力学（FEA）**、**流体力学（CFD）**、**マルチフィジックス**の内製ソルバおよび／またはアダプタ。
- **Optimization**：**トポロジー／形状／寸法**最適化、補強・軽量化、シミュレーション駆動の設計ループ。
- **AI Assistance**：拘束推定、フィーチャ意図推定、設計空間探索、ソルバ設定提案のためのエンジニアリング「コパイロット」。
- **Extensibility**：安定したプラグイン／スクリプティング API を備えたモジュラーアーキテクチャ。

> **Status**：開発中（pre‑alpha）。API とファイル形式は変更される可能性があります。

---

## Product Overview

SolidDesigner（ブランド：**Breptera**）は、再利用可能な **Alice** プラットフォーム上に構築された、**デスクトップ／ワークベンチ指向**の CAD アプリケーションです。

<p align="center">
  <img src="Docs/screenshots/home_workbench.png" width="900" alt="SolidDesigner Home Workbench" />
</p>

**ユーザー向けの目標**

- **Workflow**：ワークベンチ、リボンコマンド、ドッキングパネル、MDI ビューポート。
- **Parametric foundation**：フィーチャ履歴ツリー、スケッチ／拘束、リビルド＆再生成パイプライン（WIP）。
- **Engineering-first**：材料、荷重／境界条件、メッシュ制御、解析結果を保持できる **CAD データモデル**（計画中）。
- **Kernel-backed geometry**：既定の B‑Rep と可視化は **OpenCascade (OCCT)**。プラットフォーム層ではマルチバックエンド描画をサポートします。

> 上のスクリーンショットは現在の UI 方向性（Home Workbench + 発見／学習パネル）を示しています。プレアルファ段階のため、正確なレイアウトは短い周期で変化します。

---

## What’s in the Box

- **基盤サブモジュール（「Alice」）** を含む、モダンな C++17/20 コードベース。
- 基盤の上に構築された **デスクトップアプリケーション**（「SolidDesigner」）。
- **Core / Data / Interaction / UI** レイヤの明確な分離。
- **フィーチャグラフ**、**パラメトリック拘束**、**診断／ロギング**、**プラグインホスティング**の初期実装。
- **CAE ソルバ（FEA/CFD）** と **最適化** に向けた長期計画。

---

## Project Layout & Architecture

**Physical Structure**

```
Physical Structure
    |
    |----- Alice  (submodule)
    |         |
    |         |---- Bootstrap
    |         |---- Core
    |         |---- Data
    |         |---- Interaction
    |         |---- UI
    |
    |----- SolidDesigner  (application)
              |
              |-- APP
              |-- DATA
              |-- Interaction
              |-- UI
              |-- Plugins
```

### Layered Architecture (high‑level)

- **Alice/Core** — プラットフォーム基盤、基本ユーティリティ（メモリ、スレッド、診断、数学、単位系、幾何抽象など）。
- **Alice/Data** — パラメトリックモデル、フィーチャ／オペレーショングラフ、拘束・寸法システム、ドキュメント／セッションサービス。
- **Alice/Interaction** — 選択／ピッキング、マニピュレータ、コマンドパイプライン、Undo/Redo トランザクション、インタラクショングラフ。
- **Alice/UI** — Qt ベース（予定）のシェル、ドッキング可能なペイン、プロパティブラウザ、リボン／メニュー／ショートカット。
- **SolidDesigner/APP** — 製品レイヤ：アプリケーションライフサイクル、永続化、プロジェクト／ワークスペース、プラグイン、スクリプティング。
- **SolidDesigner/DATA/Interaction/UI** — Alice レイヤ上の製品固有拡張。

> **Alice** サブモジュールは再利用可能なエンジン層として意図されており、**SolidDesigner** がそれを組み合わせて完全な製品として構成します。

---

## Core Concepts

- **Feature Graph**：Sketch、Extrude、Revolve、Fillet、Pattern、Boolean など、すべてのモデリング操作は **履歴と依存関係** を持つ有向非巡回グラフのノードとして表現されます。再構築は決定的に伝播します。
- **Constraint System**：幾何拘束と寸法拘束を、差し替え可能なソルババックエンドとともに扱います（現状はスケッチ拘束、3D 拘束は計画中）。
- **Parametric Design**：名前付きパラメータ（寸法、材料、境界条件など）が幾何と解析の双方を駆動し、式と単位系をサポートします。
- **Simulation‑Driven Design**：解析によって候補設計を評価し、結果をパラメータへフィードバックします（例：応力目標を満たすまで板厚を自動的に減らす）。
- **Multi‑representation Geometry**：公差を考慮したソリッド／サーフェス／B‑Rep 抽象化、解析向けメッシュ生成、CAD↔CAE の整合性。
- **Transactions**：すべてのコマンドはトランザクション内で実行され、完全な Undo/Redo と診断エンジンによる意味のあるエラーメッセージを提供します。

---

## Capabilities

### CAD (current/planned)

- 拘束と寸法を備えたスケッチ
- 履歴ベースモデリング：押し出し／回転／スイープ／ロフト、フィレット／面取り、シェル、パターン、ブーリアン演算
- アセンブリ：メイト／拘束、トップダウンコンテキスト（WIP）
- 製図：ビュー、断面、寸法、GD&T（計画中）

### CAE (current/planned)

- **Structural (FEA)**：線形静解析、モーダル解析、材料ライブラリ、境界条件、メッシュ制御（段階的拡張を計画）
- **CFD**：非圧縮流（定常／非定常）、乱流モデル、境界条件（計画中）
- **Multiphysics**：熱構造連成、FSI（長期計画）

### Optimization (planned)

- トポロジー最適化（SIMP／レベルセット）
- 形状／寸法最適化、各種制約（応力、変位、固有振動数、圧力損失など）
- 設計空間探索、サロゲートモデル

### AI Assistance (planned)

- ユーザー操作からの拘束／フィーチャ意図推定
- コマンド補完、パラメータ提案
- 設計空間の推奨、DOE の自動化
- 文脈に基づくソルバ設定・メッシング提案

> 項目単位の進捗は **[Roadmap](#roadmap)** と **JIRA** を参照してください。

---

## Roadmap

計画とバックログは **JIRA** で追跡しています：  
https://hananiah.atlassian.net/jira/software/c/projects/AL/boards/3

高レベルのマイルストーン（変更される可能性があります）：

1. **P0 — Modeling Foundations**：安定したフィーチャグラフ、堅牢なスケッチャ、基本モデリング操作、トランザクションシステム、永続化。
2. **P1 — Meshing & FEA MVP**：四面体／六面体メッシュパイプライン、線形静解析／モーダル解析、基本ポスト処理。
3. **P2 — CFD MVP**：非圧縮流向けのメッシュとソルバ統合、圧力／速度／温度場、ポスト処理。
4. **P3 — Optimization**：SIMP トポロジー最適化、閉ループのパラメータ更新、制約処理。
5. **P4 — AI Copilot v1**：拘束推定、コマンド提案、ソルバプリセット、プロジェクト履歴からの学習。

詳細設計ドキュメントは **Confluence**（要アクセス権）にあり、公開可能な一部は **GitHub Wiki** にあります。

---

## Build & Run

このリポジトリには、`../SolidDesigner_Build/` にビルドツリーを生成する **ワンクリックビルドスクリプト** が含まれています。

### Prerequisites (current)

- **CMake ≥ 3.31**  
  - Windows：リポジトリには `ToolChain/cmake` 配下に CMake が同梱されており、`AutoGenerateVsProject.bat` がそれを利用します。  
  - Linux：新しめの CMake をシステムへインストールするか、独自ツールチェーンを使ってください。
- **C++17 toolchain**：MSVC v143 / GCC 11+ / Clang 15+
- **Qt 5.15.x**（Core, Gui, Widgets, Network, Quick, Qml モジュール）
- **OpenCascade (OCCT) SDK**：OCCT Viewer バックエンド用（以下の SDK レイアウトを参照）

### Windows (Visual Studio 2022, x64)

1. サブモジュール付きでクローンします：

```bash
git clone --recurse-submodules https://github.com/hananiahhsu/SolidDesigner.git
cd SolidDesigner
```

2. 次を実行します：

- `AutoGenerateVsProject.bat`（`../SolidDesigner_Build/SolidDesigner.sln` を生成して Visual Studio を開きます）

3. Visual Studio で `Release|x64` 構成をビルドし、その後 `SolidDesigner` を実行します。

### Linux (Makefiles)

次を実行します：

```bash
./SolidDesignerForLinux.sh
```

このスクリプトは `Unix Makefiles` を使って構成とビルドを行い、出力を `../SolidDesigner_Build/` に生成します。

> 注意：現在このスクリプトは `-DCMAKE_GENERATOR_PLATFORM=x64` を渡しています。これは Visual Studio 向けのオプションであり、Linux ツールチェーンでは無視される場合があります。問題がある場合は、次の「Manual CMake」を使って手動で構成してください。

### Manual CMake (recommended when customizing toolchains)

```bash
cmake -S . -B ../SolidDesigner_Build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build ../SolidDesigner_Build --parallel
```

### Third‑party SDK layout (OCCT)

OCCT Viewer バックエンドは、OpenCascade SDK が次の場所へエクスポートされていることを前提としています：

```
Externals/3rdParty/sdk/<platform>/<Debug|Release>/occt
```

既定の `<platform>` 値（上書き可能）：

- Windows：`msvc2022-x64-md`
- Linux：`linux-x64`

CMake から次のように上書きできます：

- `-DSD_3P_PLATFORM=...`
- `-DSD_3P_CFG=Debug|Release`
- または `OpenCASCADEConfig.cmake` を含むフォルダを `-DOpenCASCADE_DIR=...` で直接指定します。

### Qt

UI ターゲットは現在 **Qt 5** を使用しています（CMake では `Qt5::Core`、`Qt5::Widgets`、`Qt5::Quick/Qml` など）。  
Windows では、一部モジュールが `Qt5.15.x` 向けの既定 `CMAKE_PREFIX_PATH` を設定しています。必要に応じて、手元の Qt インストール先に合わせて調整してください。

---

## Dependencies

このプロジェクトはモジュラー構成で、一部のライブラリは **リポジトリ内に同梱** され、他は **外部 SDK** として導入される想定です。

### Open-source Stack & Licenses

| ライブラリ | 用途 | 配置場所 | ライセンス（上流） |
|---|---|---|---|
| **OpenCascade (OCCT)** | B‑Rep カーネル + OCCT Viewer バックエンド | `Alice/Core/Runtime/AliceRenderBackendOCCViewer` | LGPL‑2.1 with OCCT exception（上流） |
| **Qt 5 (Widgets/Quick/Qml)** | デスクトップ UI（リボン、パネル、ダイアログ） | `Designer/UI/*`, `Alice/UI/QFrameWork/*` | GPL/LGPL/commercial（Qt） |
| **spdlog** | ロギングバックエンド | `Alice/Core/Foundation/AliceBasicTool/*SpdLog*` | MIT |
| **fmt** | 文字列フォーマット | `Alice/Core/Foundation/AliceBasicTool/*Fmt*` | MIT |
| **Open Sans** | リボン用フォントアセット | `Alice/UI/QFrameWork/AliceRibbon/OpenSans` | Apache‑2.0 |
| | | | |
| | | | |

> **ライセンス注記**：SolidDesigner は **GPLv3** ですが、同梱／必須依存には LGPL/MIT/Apache が含まれます。バイナリを再配布する場合は、各上流ライセンスの条件（動的リンク義務、告知、ソース提供など）を順守してください。

### Optional / planned adapters (not required for a minimal build)

- **OGRE / OSG / VTK / Skylark** の描画バックエンドは、プラットフォームモジュール（`Alice/Core/Runtime/AliceRenderBackend*`）として存在しますが、追加 SDK が必要な場合があり、現在も進化中です。
- **メッシング／ソルバ**（FEA/CFD/最適化）は活発に設計中であり、アダプタは段階的に導入されます。

---

## Getting Started

典型的なワークフローの目標形は次のとおりです：

1. **プロジェクトを作成**し、既定の単位系と公差を設定します。
2. 平面上に **スケッチ** し、拘束と寸法を適用します。
3. **Extrude**、**Revolve**、**Fillet**、**Shell**、**Pattern** などのフィーチャを作成します。
4. パーツを **アセンブリ** し、メイト／拘束を追加します。
5. モデルを **メッシュ化** します（グローバル + ローカル制御）。
6. **材料** と **境界条件** を定義します。
7. **FEA/CFD** を実行し、応力／ひずみ、モード、流れ場を確認します。
8. 結果から **パラメータを駆動** します（例：応力 ≤ 目標値になるまで厚みを減らす）。
9. **プロジェクト** として保存し、**STEP/IGES** またはメッシュ形式へエクスポートします。

---

## Plugin & Scripting

- **Plugin ABI**：幾何操作、メッシング、ソルバ、インポータ／エクスポータ、UI アドイン向けのクリーンな C++ インターフェース。
- **Isolation**：安定した所有権モデルと DLL 境界をまたぐ安全性（基盤は Owning/Weak/Guard ポインタユーティリティを提供）。
- **Scripting (planned)**：モデリング自動化、スタディ設定、ポスト処理、設計ループのオーケストレーションのための Python API。
- **AI hooks (planned)**：意図予測や最適化のためのカスタム設計アドバイザや ML モデルを登録可能にするフック。

---

## Data & File Formats

### Native project format (in progress)

ネイティブ形式は次の性質を備えることを意図しています：

- **Structured**：メタデータ + 型付きペイロード（幾何、メッシュ、結果、サムネイルなど）
- **Versioned**：明示的なアップグレードパイプラインを備えたスキーマバージョニング
- **Incremental-friendly**：部分リロードや将来のクラウド／ワークスペースワークフローを見据えた設計
- **Stable-identity aware**：保存／読込、コピー＆ペースト、アップグレードをまたいでもオブジェクト ID を維持

> 形式が安定した段階で、公開 Wiki に正規仕様を掲載する予定です。

### Interoperability (planned / incremental)

- **CAD Interop**：STEP/IGES のインポート／エクスポート（他形式はアダプタ経由）
- **Mesh/Results**：外部ソルバやポスト処理向けの標準メッシュ／結果形式（VTK、MED など、計画中）
- **Units**：明示的なメタデータを伴う一貫した単位系、式内の次元付きパラメータ

---

## Diagnostics, Logging & QA

- 重大度レベル、ソース位置、差し替え可能なシンク（コンソール、ファイル、UI パネル）を備えた統一 **DiagnosticsEngine**。
- 高速でスレッド対応なロギングのための任意の **spdlog** バックエンド。
- DLL 境界をまたぐ **assertion** と **防御的チェック**。
- CTest による **テスト**：幾何、メッシング、ソルバ正当性のフィクスチャ。再現ケースは JIRA に添付可能。

---

## Contributing

コントリビューションを歓迎します。

- 背景理解のために、JIRA のエピック／タスクと GitHub Wiki を確認してください。
- 大きな提案は PR を開く前に議論してください。
- プロジェクトのコードスタイル（clang-format は予定）に従い、ユニットテストを含めてください。
- コミットは小さく、内容が分かるように記述し、可能であれば JIRA チケットにリンクしてください。

最初のコントリビューション候補：

- 特定プラットフォーム／コンパイラでのビルド問題を修正する
- 集中したテストを追加する（幾何、永続化、拘束解法）
- ドキュメントを追加する：設計ノート、図、最小限の「How it works」セクションなど

> リポジトリレベルの貢献ドキュメント（計画中）：`CONTRIBUTING.md`、`CODE_OF_CONDUCT.md`。

---

## License

このリポジトリは **GNU GPL v3.0** の下でライセンスされています。全文は `LICENSE` を参照してください。

> 注：サードパーティライブラリは独自ライセンスを持つ場合があります。バイナリ再配布時は各ライセンスへの準拠を確認してください。

---

## Acknowledgments

本プロジェクトは、OpenCascade、Eigen、fmt、spdlog、Qt、そして広範なオープンソースコミュニティの成果の上に成り立っています。  
CAD/CAE/CFD/最適化分野のコントリビュータと研究者の皆様に感謝します。

---

## FAQ

**スクリプト API はありますか？**  
Python API は計画中です。初期的な内部足場はありますが、公開 API は今後提供予定です。

**どのソルバスタックを使っていますか？**  
初期の内製ソルバを試作中です。外部ソルバ（メッシャ／ポストなど）向けアダプタも計画しています。

**AI 機能にはインターネット接続が必要ですか？**  
いいえ。ローカルモデルによるオフライン推論を基本とし、必要に応じてクラウド連携もサポートする方針です。

**進捗はどこで追えますか？**  
JIRA（ロードマップ／バックログ）と公開 GitHub Wiki で追えます。詳細設計ドキュメントは Confluence（要アクセス権）にあります。
