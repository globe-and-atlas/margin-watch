---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-06T21:20:26-06:00"
---
# Margin — published round update

Goal: publish the verified multi-platform release with round screenshots.
Agent: OpenAI Codex
Handoff-from: OpenAI Codex
Handoff-type: continuation
Status: published and public assets independently verified

## Result
- Version0.1.1 is public: [Margin](https://apps.repebble.com/f08ced3e3a9a47efb297dd3c).
- Native binaries cover Emery200×228, Chalk180×180, and Gabbro260×260. Original UUID/settings mappings preserved.
- Two native screenshots appear under each round watch selection.
- Existing appID and original gallery bytes preserved; animated first preview unchanged.
- User explicitly excluded T9; its public release/gallery remain unchanged.

## Evidence
- Public PBW SHA-256 matches the reviewed production artifact: `0ef44160c776a92f9394fa5338004be6bc3d1bb161e5b211de81368a90c86f25`.
- Four public round images decode to exact native source pixels. Both watch selections were checked in the public UI.
- Fresh independent verifier accepted all15PBWs,60round images, sixnewGIFs, existing9galleries, and unchangedT9.
- Upload guards/read-retry/failure-path tests:5passed. No repeated release uploads were used for screenshot correction.
- No Git commits or pushes were performed. Physical-device testing remains separate.

## Artifacts and continuation
- `release/store-release.json`: current verified receipt.
- `release/round-update/0.1.1/public-proof.json`: public asset URLs and assertions.
- `media/store/round-update/`: native round listing assets and release plan.
- [Round store workflow](procedural/publish_round_update.md); [local validation archive](sessions/2026-11-06-round-local-validation.md).

S.D.G.: Lets owners of either round Pebble install Margin from the public store with accurate native previews.
Feynman gap: Public bytes and preview pixels are verified; physical-watch readability and endurance remain device checks.
