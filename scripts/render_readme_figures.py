"""Generate explanatory SVG diagrams; no measurements or real camera frames."""
from pathlib import Path
from html import escape

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'docs/figures'


class Figure:
    def __init__(self,title,description,width=1200,height=630):
        self.parts=[f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}" role="img" aria-labelledby="title desc">',
          f'<title id="title">{escape(title)}</title><desc id="desc">{escape(description)}</desc>',
          f'<rect width="{width}" height="{height}" fill="#f7fafc"/>',
          '<style>text{font-family:Arial,Helvetica,sans-serif;fill:#172b42}</style>',
          '<defs><marker id="arrow" markerWidth="8" markerHeight="8" refX="7" refY="4" orient="auto"><path d="M0 0L8 4L0 8" fill="#637992"/></marker></defs>']
        self.text(48,52,title,28,bold=True)
        self.text(48,82,description,16,color='#566a82')
    def text(self,x,y,label,size=18,color='#172b42',bold=False):
        self.parts.append(f'<text x="{x}" y="{y}" font-size="{size}" fill="{color}" font-weight="{"bold" if bold else "normal"}">{escape(label)}</text>')
    def box(self,x,y,w,h,title,lines,color='#e3f1f4'):
        self.parts.append(f'<rect x="{x}" y="{y}" width="{w}" height="{h}" rx="15" fill="{color}" stroke="#c5d4e4"/>')
        self.text(x+20,y+34,title,20,bold=True)
        for i,line in enumerate(lines):self.text(x+20,y+65+i*25,line,16)
    def arrow(self,x1,y1,x2,y2):
        self.parts.append(f'<line x1="{x1}" y1="{y1}" x2="{x2}" y2="{y2}" stroke="#637992" stroke-width="2.5" marker-end="url(#arrow)"/>')
    def save(self,name):
        (OUT/name).write_text('\n'.join(self.parts+['</svg>']),encoding='utf-8')


def main():
    OUT.mkdir(parents=True,exist_ok=True)
    f=Figure('Vision → track handling → closed-loop actuation',
             'System overview for the TC264 smart-car firmware; conceptual data flow, not a timing trace.')
    f.box(48,120,250,130,'01 · Camera',['MT9V03X grayscale frames','Track appearance'], '#e3f1f4')
    f.box(340,120,320,130,'02 · Perception',['Threshold / boundary processing','Lane and centerline geometry'], '#e3f1f4')
    f.box(705,120,445,130,'03 · Track-aware guidance',['Roundabout and intersection logic','Repaired path / steering guidance'], '#e3f1f4')
    f.arrow(298,185,332,185);f.arrow(660,185,697,185)
    f.box(48,315,385,150,'Feedback and tuning',['Encoder pulse feedback','LCD / keyboard / debug support'], '#eef0fb')
    f.box(490,315,300,150,'04 · Control',['Steering and speed regulation','Track-dependent speed setting'], '#eef0fb')
    f.box(850,315,300,150,'05 · Actuation',['Servo PWM','Motor direction and PWM'], '#eef0fb')
    f.arrow(927,250,640,307);f.arrow(433,390,482,390);f.arrow(790,390,842,390)
    f.text(48,530,'Execution split described in the original project:',18,bold=True)
    f.text(48,565,'CPU1 · frame processing     |     CPU0 · peripheral interaction and control',18)
    f.text(48,603,'Scheduling latency and cross-core synchronization need on-board verification.',16,color='#566a82')
    f.save('smart-car-architecture.svg')

    f=Figure('From road boundaries to steering guidance',
             'Illustrative lane geometry only — not a captured frame or replay of this firmware.')
    f.parts.append('<rect x="48" y="120" width="610" height="455" rx="16" fill="#16243a"/>')
    for path,color,width in [('M 140 550 C 205 420 345 370 335 150','#47d2d0',7),
                             ('M 600 550 C 500 420 435 360 400 150','#e9bc67',7),
                             ('M 370 550 C 350 420 390 365 367 150','#eaf1ff',4)]:
        f.parts.append(f'<path d="{path}" fill="none" stroke="{color}" stroke-width="{width}"/>')
    f.parts.append('<line x1="370" y1="550" x2="370" y2="150" stroke="#8ca0ba" stroke-width="2" stroke-dasharray="8 8"/>')
    f.parts.append('<circle cx="389" cy="350" r="9" fill="#fa827d"/>')
    f.text(82,155,'far',16,color='#eaf1ff');f.text(82,548,'near',16,color='#eaf1ff')
    f.box(705,130,445,130,'Boundary extraction',['Locate left and right track limits','Handle discontinuities with track logic'])
    f.box(705,285,445,130,'Path reconstruction',['Repair missing boundary segments','Estimate the centerline'])
    f.box(705,440,445,130,'Guidance',['Turn path geometry into steering input','Keep perception and control connected'])
    f.text(48,610,'Teal: left boundary   ·   Gold: right boundary   ·   White: centerline   ·   Red: illustrative target',15)
    f.save('smart-car-lane-geometry.svg')

    f=Figure('Track-aware speed settings in the source code',
             'Selected branches in speed_get(); fractions of Set_Speed1, not measured vehicle speeds.')
    labels=['Reference setting','Roundabout (junsu = 0)','Intersection','poer_flag branch','Stop / out-of-track flag']
    fractions=[1,.85,.75,.55,0]
    for i,(label,value) in enumerate(zip(labels,fractions)):
        y=145+i*75
        f.text(48,y+25,label,18)
        f.parts.append(f'<rect x="360" y="{y}" width="660" height="36" rx="5" fill="#e4ebf3"/>')
        if value:f.parts.append(f'<rect x="360" y="{y}" width="{660*value}" height="36" rx="5" fill="#147d92"/>')
        f.text(1040,y+25,f'{value:.0%}',20,bold=True)
    f.text(48,562,'Other modes use different rules; the ordinary non-stop branch can add a geometry-dependent term.',15)
    f.text(48,603,'Source: CODE/control.c. Configuration illustration; not an experimental performance result.',16,color='#566a82')
    f.save('smart-car-speed-policy.svg')
    print('Generated three documented SVG figures.')


if __name__=='__main__':main()
