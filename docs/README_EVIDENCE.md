# Documentation evidence

Review date: 2026-10-02.

Sources examined:

- [Original overview](https://github.com/ashley-tech628/vision-guided-autonomous-smart-car): hardware, reported award, core division and contributions.
- [image_deal.c](https://github.com/ashley-tech628/vision-guided-autonomous-smart-car/blob/main/CODE/image_deal.c): Ostu, image access, advanced_regression and Center_line_deal.
- [control.c](https://github.com/ashley-tech628/vision-guided-autonomous-smart-car/blob/main/CODE/control.c): speed_get branches, PWM/direction writes and encoder counter operations.
- [traffic_cricle.c](https://github.com/ashley-tech628/vision-guided-autonomous-smart-car/blob/main/CODE/traffic_cricle.c): turning-point searches and interpolated repairs.

The web reader returned cached pages. No Git clone or firmware rebuild succeeded in the assistant's restricted environment. Recheck source branches in a current checkout before applying the update if they have changed.

The architecture figure is conceptual. CPU division comes from the original overview, not independently inspected startup code; no measured period or synchronization guarantee is asserted.

The lane figure is illustrative geometry, not an actual frame or execution result.

The speed chart depicts selected Set_Speed1 fractions. Roundabout 85% refers to junsu == 0, not every mode. poer_flag retains its source name because its physical meaning was not independently established. The 100% bar is a reference, not the ordinary branch, which can add an acceleration term.

No lap-time measurements, success rates or real-car photographs were invented. Award wording comes from the original overview; competition name, year and award level were not inferred.
