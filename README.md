# Open Salad Mix

**An open-source table-top salad mixer for the circular economy.**
Open Salad Mix gently mixes salad and dressing by slowly rolling a closed food-safe jar on motor-driven rollers – no blades, no bruised leaves. Every designed part can be 3D-printed in a FabLab, wear parts are easy to replace, and all design files are open.

> GPE Project 2026/27 – TU Berlin × Vietnamese-German University (VGU) · Phase 1 release (Nov 2026)

![Open Salad Mix – CAD](BOM list & 3D explosion view & Assembling\3D explosion view)

---

## How it works

1. Fill the jar with salad and dressing – at most 65 % full – and close the lid.
2. Lift the upper roller and rest it on the two slider holders. Lay the closed jar on the two lower rollers and lower the upper roller onto it – two extension springs keep it pressed on the jar.
3. Plug in the power adapter, choose one of three speeds with the speed selector and set the timer knob – the machine starts.
4. The motor drives one lower roller through a 3:1 timing belt; friction turns the jar slowly. The salad is lifted and rolls down again, so the dressing coats every leaf.
5. The machine stops automatically when the timer runs out. Unplug the adapter after use.

## Key specification

| Item            | Value                                                                                            |
| --------------- | ------------------------------------------------------------------------------------------------ |
| Jar             | Food-contact PET jar Ø120 × 200 mm with lid and seal                                             |
| Rollers         | 3 × TPU 95A roller sleeves Ø40 mm on Ø8 stainless shafts (sleeves are wear parts)                |
| Holding the jar | Upper roller pulled down by 2 extension springs; rests on the slider holders when open           |
| Drive           | JGB37-520 12 V DC gear motor with encoder, GT2 timing belt 20T → 60T (3:1)                       |
| Control         | Arduino Leonardo + BTS7960 motor driver; 3-speed selector; rotary timer starts and stops the run |
| Power           | MEAN WELL 12 V DC adapter (5 A, 60 W) – low voltage only                                         |
| Size            | ≈ 320 × 220 mm footprint – fits in hand luggage                                                  |
| Cost            | ≈ €123 for all parts, shipping not included (budget ≤ €200) – see BOM                            |

## Repository structure

| Folder / file                      | Content                                                                        |
| ---------------------------------- | ------------------------------------------------------------------------------ |
| `README.md`                        | This file – start here                                                         |
| `LICENSE`                          | CERN-OHL-S-2.0 licence text                                                    |
| `BOM_Open_Salad_Mix_final_v2.pdf`  | Bill of materials – all printed and purchased parts with quantities and prices |
| `OpenSalad_Mix_Assembly_Guide.pdf` | Step-by-step assembly (12 steps) + checks after assembly                       |
| `3D Model/3D Print/`               | STEP file of every printed part (P001–P009)                                    |
| `3D Model/3D print file.3mf`       | Print-ready 3MF file of the printed parts                                      |
| `3D Model/Hardware/`               | STEP files of purchased parts (reference only)                                 |
| `3D Model/Assembly.f3z`            | Autodesk Fusion 360 archive of the full assembly                               |
| `3D Model/Assembly.step`           | STEP of the full assembly – opens in any CAD tool                              |
| `src/Wiring Diagram.jpg`           | Wiring diagram                                                                 |
| `src/motor_spin_timer/`            | Arduino firmware (`motor_spin_timer.ino`)                                      |
| `images/`                          | Product picture used in this README                                            |

## How to start

1. Check the **BOM** (`BOM_Open_Salad_Mix_final_v2.pdf`).
2. Order the purchased parts listed in the BOM.
3. Print the parts in `3D Model/3D Print/` (or use `3D Model/3D print file.3mf`) – PETG / PETG-CF, Roller Sleeves and Feet in TPU 95A.
4. Assemble the machine following the **Assembly Guide** (`OpenSalad_Mix_Assembly_Guide.pdf`): Base → Lower roller unit → Upper roller unit. Wire the electronics according to `src/Wiring Diagram.jpg` and upload `src/motor_spin_timer/motor_spin_timer.ino` with the Arduino IDE.

## Repair and wear parts

- **TPU roller sleeves** – pull them off the shaft and print new ones from the STL files.
- **Timing belt** – standard GT2 belt, 6 mm wide, 240 mm long.
- **Extension springs** – hooked in, replace without tools.

All parts are screwed or press-fitted (no glue), so the machine can be taken apart with a screwdriver. Motor and electronics can be removed and reused.

## Possible upgrades & interfaces

Ideas for the next group (Phase 2):

- Display showing the remaining mixing time
- Clip-in mixing ribs inside the jar for better tumbling
- A second jar size
- App or Bluetooth control

Reserved interfaces: free I/O pins on the Arduino Leonardo, spare space in the base housing, all speed values in one parameter table in the firmware.

## Licence

All files in this repository – hardware design files, documentation and firmware – are licensed under the **CERN Open Hardware Licence Version 2 – Strongly Reciprocal ([CERN-OHL-S-2.0](https://ohwr.org/cern_ohl_s_v2.txt))**. See `LICENSE`.

## Attribution

The STEP models of purchased parts in `3D Model/Hardware/` (Arduino Leonardo, selector, motor, bearing, spring, screw) are taken from the manufacturers' or suppliers' websites and stay under their owners' terms; they are included for reference only.

**Tools used:** Autodesk Fusion 360 (CAD – native files + STEP exports) · Arduino IDE (firmware)

## Team

Đào Thiện Bình (mechanical engineering) · Hoàng Lê Gia Bảo (design framework & control) · Nguyễn Thị Hồng Loan (architecture, BOM & documentation) · Phạm Tăng Thanh Dung (requirements, repository & documentation) · Phạm Võ Tấn Hưng (repository & release)

## Disclaimer

This is a student project. Build and use it at your own risk. Use only the supplied food-safe jar, keep fingers away from the rollers and the belt while the machine is running, and unplug the power adapter before cleaning or repair.
