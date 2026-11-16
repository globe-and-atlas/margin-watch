---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-05T15:40:00-06:00"
---
# Margin
A Pebble Time 2 watchface with oversized stacked time and a narrow date/battery sidebar.

- Six palettes plus custom background, text and accent.
- Watch-default, 12-hour or 24-hour time; explicit AM/PM in 12-hour mode.
- Date Off, word date, ISO, US or EU; numeric formats stack their parts in that order.
- Real battery percentage and four-block battery icon.
- Sidebar progress line represents the current minute within the hour (00 empty;59full).

## Build
`node watchface/settings.test.js`
`python3 -m pytest tests/ -q`
`python3 execution/build.py`
`python3 execution/verify.py`

Install `dist/Margin-0.1.0.pbw`. Live on the Pebble app store: [Margin](https://apps.repebble.com/f08ced3e3a9a47efb297dd3c).

## Native QA
Fixture-only builds accept time/battery overrides; production builds strip MARGIN_* environment flags. Screenshots in media are actual 200×228 emulator pixels. Font: Archivo Black, bundled OFL license in licenses/.

## Public release
https://apps.repebble.com/f08ced3e3a9a47efb297dd3c

Version 0.1.0. First gallery image cycles through 6native color palettes; four static previews follow. Public GIF and production PBW verified against local release files.


## Round-compatible release — 0.1.1

Margin includes native layouts for Pebble Time2 (Emery200×228), original Time Round (Chalk180×180), and Round2 (Gabbro260×260). The rectangular layout and existing settings identities are preserved.

Build: `python3 execution/build.py`, then `python3 execution/verify.py`. Local bundle: `dist/Margin-0.1.1.pbw`. Native round previews: `media/round/`. Repeatable fixture/capture instructions: [round compatibility QA](knowledge/procedural/round_compatibility.md).

This update is [publicly available](https://apps.repebble.com/f08ced3e3a9a47efb297dd3c) with round screenshots. Public PBW bytes and screenshot pixels verify; physical-watch validation remains separate.
