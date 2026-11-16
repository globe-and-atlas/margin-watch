---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-05T15:20:00-06:00"
---
# Margin — native first version

## Contract
- Surface: separate Emery-only watchface matching the selected Margin render.
- Directive: directives/build_watchface.md.
- Execution: generate_digits.py, build.py, verify.py, capture_native.py.
- Output: dist/Margin-0.1.0.pbw; native media.
- Authorization: user approved public store publication with a palette GIF first.
- Safety: do not read .env; do not commit .tmp; serialize shared emulator access.

## Validation contract
- [x] Production PBW exists.
- [x] Native default time has two large stacked rows.
- [x] Native sidebar contains the date.
- [x] Native sidebar contains actual battery percentage.
- [x] 12-hour mode shows AM/PM.
- [x] 24-hour mode displays 00 at midnight.
- [x] Date Off hides date text.
- [x] ISO date shows year, month, day in that order.
- [x] US date shows month, day, year in that order.
- [x] EU date shows day, month, year in that order.
- [x] Six preset palettes render.
- [x] Custom colors render.
- [x] Clay Save sends normalized values.
- [x] Clay Cancel sends no changes.
- [x] Settings persist after relaunch.
- [x] Host tests pass.
- [x] A fresh verifier reviews source and native outputs.

## Master's brief
Primary good: Clarity, through immediately readable time.
Stone removed: use proven settings plumbing; distinct renderer owns its geometry.
Human mark: Daniel selects whether the native shape preserves the concept.
Non Finito: physical wrist judgment and publication remain open.
Structural weakness: a generated concept can exaggerate available screen space.
Myth under test: huge time plus a 44px sidebar fits natively; inspect worst-case 23:59 and full dates; shrink sidebar labels if overlap occurs.
Misericord: date-format order and settings cancellation deserve the same care as default art.
S.D.G.: Quick readable time for Pebble Time 2 owners.
Feynman gap: native appearance verified; physical-watch contrast remains untested.

## Verified completion
- 19native fixture cases passed.
- Settings persisted pixel-identically after app relaunch.
- Clean production bundle installed; live time/currentbattery screenshot observed.
- Independent read-only reviewer passed source and native outputs.
- Initial implementation was local-only; public release is tracked below.

## Store release —2026-11-05
- [x] Palette GIF contains native200×228frames.
- [x] Each GIF frame matches its source capture.
- [x] First GIF frame shows the default palette.
- [x] GIF pauses at least2500ms per palette.
- [x] Listing description enumerates supported options.
- [x] Production bundle passes verification.
- [x] Store listing is publicly available.
- [x] Public first preview is the palette GIF.
- [x] Public GIF bytes match the approved local file.
- [x] Public PBW bytes match the archived release.
- [x] A fresh verifier reviews release evidence.

## Round compatibility — 2026-11-06
- [x] Emery remains a build target.
- [x] Chalk is a build target.
- [x] Gabbro is a build target.
- [x] The UUID is preserved.
- [x] Existing settings key mappings are preserved.
- [x] Native Chalk layout passes visual review.
- [x] Native Gabbro layout passes visual review.
- [x] Clean production PBW contains three native binaries.
- [x] Existing host/settings checks pass.
- [x] Fresh independent review passes.
No store publication is authorized by this compatibility request.

## Store round update — 2026-11-06
- [x] Publish the verified three-platform production update.
- [x] Preserve the current animated preview.
- [x] Add native screenshots for Chalk.
- [x] Add native screenshots for Gabbro.
- [x] Verify the public download matches the production artifact.
- [x] Verify public round screenshot pixels.
- [x] Fresh independent public-proof review passes.
