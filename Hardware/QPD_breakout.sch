<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="yes" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="yes" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="yes" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="yes" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="yes" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="yes" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="yes" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="yes" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="yes" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="yes" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="yes" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="yes" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="yes" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="yes" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="yes" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="yes" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="yes" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="yes" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="yes" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="yes" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="yes" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="yes" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="yes" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="yes" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="yes" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="yes" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="yes" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="yes" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="yes" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="yes" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="yes" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="yes" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="yes" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="yes" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="yes" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="yes" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="AGND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<wire x1="-1.0922" y1="-0.508" x2="1.0922" y2="-0.508" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="AGND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="AGND" prefix="AGND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="VR1" symbol="AGND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-subd">
<description>&lt;b&gt;SUB-D Connectors&lt;/b&gt;&lt;p&gt;
Harting&lt;br&gt;
NorComp&lt;br&gt;
&lt;p&gt;
PREFIX :&lt;br&gt;
H = High density&lt;br&gt;
F = Female&lt;br&gt;
M = Male&lt;p&gt;
NUMBER: Number of pins&lt;p&gt;
SUFFIX :&lt;br&gt;
H = Horizontal&lt;br&gt;
V = Vertical &lt;br&gt;
P = Shield pin on housing&lt;br&gt;
B = No mounting holes&lt;br&gt;
S = Pins individually placeable (Single)&lt;br&gt;
D = Direct mounting &lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="F15D">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<wire x1="-12.319" y1="6.9342" x2="-11.811" y2="7.4422" width="0.1524" layer="21" curve="-90"/>
<wire x1="11.684" y1="7.4422" x2="12.192" y2="6.9342" width="0.1524" layer="21" curve="-90"/>
<wire x1="-12.319" y1="1.8542" x2="-12.319" y2="6.9342" width="0.1524" layer="21"/>
<wire x1="-12.954" y1="1.2192" x2="-12.319" y2="1.8542" width="0.1524" layer="21" curve="90"/>
<wire x1="12.192" y1="1.8542" x2="12.192" y2="6.9342" width="0.1524" layer="21"/>
<wire x1="12.192" y1="1.8542" x2="12.827" y2="1.2192" width="0.1524" layer="21" curve="90"/>
<wire x1="-11.811" y1="7.4422" x2="11.684" y2="7.4422" width="0.1524" layer="21"/>
<wire x1="-11.7856" y1="0.508" x2="-11.7856" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-11.7856" y1="0.508" x2="-11.6586" y2="0.508" width="0.1524" layer="21"/>
<wire x1="-11.6586" y1="-1.905" x2="-11.0236" y2="-2.54" width="0.1524" layer="21" curve="90"/>
<wire x1="-11.6586" y1="-1.905" x2="-11.6586" y2="0.508" width="0.1524" layer="21"/>
<wire x1="-11.043" y1="-2.54" x2="11.043" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="11.7856" y1="0.508" x2="11.7856" y2="1.016" width="0.1524" layer="21"/>
<wire x1="11.6586" y1="-1.905" x2="11.6586" y2="0.508" width="0.1524" layer="21"/>
<wire x1="11.6586" y1="0.508" x2="11.7856" y2="0.508" width="0.1524" layer="21"/>
<wire x1="11.0236" y1="-2.54" x2="11.6586" y2="-1.905" width="0.1524" layer="21" curve="90"/>
<wire x1="-17.8308" y1="-2.7432" x2="-16.4592" y2="-4.1148" width="0" layer="48"/>
<wire x1="-16.4592" y1="-4.1148" x2="-15.0876" y2="-2.7432" width="0" layer="48"/>
<wire x1="-15.0876" y1="-2.7432" x2="-13.716" y2="-4.1148" width="0" layer="48"/>
<wire x1="-13.716" y1="-4.1148" x2="-12.3444" y2="-2.7432" width="0" layer="48"/>
<wire x1="12.3444" y1="-2.7432" x2="13.716" y2="-4.1148" width="0" layer="48"/>
<wire x1="13.716" y1="-4.1148" x2="15.0876" y2="-2.7432" width="0" layer="48"/>
<wire x1="15.0876" y1="-2.7432" x2="16.4592" y2="-4.1148" width="0" layer="48"/>
<wire x1="16.4592" y1="-4.1148" x2="17.8308" y2="-2.7432" width="0" layer="48"/>
<smd name="1" x="-9.6014" y="-6.0448" dx="1.7" dy="3.5" layer="1"/>
<smd name="2" x="-6.858" y="-6.045" dx="1.7" dy="3.5" layer="1"/>
<smd name="3" x="-4.1146" y="-6.0448" dx="1.7" dy="3.5" layer="1"/>
<smd name="4" x="-1.3718" y="-6.0448" dx="1.7" dy="3.5" layer="1"/>
<smd name="5" x="1.3718" y="-6.0446" dx="1.7" dy="3.5" layer="1"/>
<smd name="9" x="-8.2296" y="-6.0452" dx="1.7" dy="3.5" layer="16"/>
<smd name="10" x="-5.4864" y="-6.0452" dx="1.7" dy="3.5" layer="16"/>
<smd name="11" x="-2.7432" y="-6.0452" dx="1.7" dy="3.5" layer="16"/>
<smd name="12" x="0" y="-6.0452" dx="1.7" dy="3.5" layer="16"/>
<smd name="6" x="4.1146" y="-6.0448" dx="1.7" dy="3.5" layer="1"/>
<smd name="7" x="6.858" y="-6.045" dx="1.7" dy="3.5" layer="1"/>
<smd name="8" x="9.6014" y="-6.0448" dx="1.7" dy="3.5" layer="1"/>
<smd name="13" x="2.7432" y="-6.0452" dx="1.7" dy="3.5" layer="16"/>
<smd name="14" x="5.4864" y="-6.0452" dx="1.7" dy="3.5" layer="16"/>
<smd name="15" x="8.2296" y="-6.0452" dx="1.7" dy="3.5" layer="16"/>
<text x="-10.2616" y="-10.16" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-0.1016" y="-10.16" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="-10.0348" y="-2.1786" size="1.27" layer="21" ratio="10">1</text>
<text x="12.8016" y="-2.54" size="1.27" layer="48">Board</text>
<text x="9.1998" y="-2.1786" size="1.27" layer="21" ratio="10">8</text>
<text x="-7.6916" y="-2.1966" size="1.27" layer="22" ratio="10" rot="MR0">9</text>
<text x="8.6566" y="-2.1966" size="1.27" layer="22" ratio="10" rot="MR0">15</text>
<text x="-11.7348" y="4.5974" size="1.27" layer="51" ratio="10">F15D</text>
<text x="-17.8816" y="-2.54" size="1.27" layer="48">Board </text>
<rectangle x1="-19.685" y1="0.8112" x2="19.558" y2="1.3192" layer="21"/>
<rectangle x1="-10.2012" y1="-6.56" x2="-9.0012" y2="-4.06" layer="51"/>
<rectangle x1="-8.8296" y1="-6.56" x2="-7.6296" y2="-4.06" layer="52"/>
<rectangle x1="-6.0864" y1="-6.56" x2="-4.8864" y2="-4.06" layer="52"/>
<rectangle x1="-3.3432" y1="-6.56" x2="-2.1432" y2="-4.06" layer="52"/>
<rectangle x1="-7.458" y1="-6.56" x2="-6.258" y2="-4.06" layer="51"/>
<rectangle x1="-4.7148" y1="-6.56" x2="-3.5148" y2="-4.06" layer="51"/>
<rectangle x1="-1.9716" y1="-6.56" x2="-0.7716" y2="-4.06" layer="51"/>
<rectangle x1="0.7716" y1="-6.56" x2="1.9716" y2="-4.06" layer="51"/>
<rectangle x1="-0.6" y1="-6.56" x2="0.6" y2="-4.06" layer="52"/>
<rectangle x1="2.1432" y1="-6.56" x2="3.3432" y2="-4.06" layer="52"/>
<rectangle x1="4.8864" y1="-6.56" x2="6.0864" y2="-4.06" layer="52"/>
<rectangle x1="7.6296" y1="-6.56" x2="8.8296" y2="-4.06" layer="52"/>
<rectangle x1="3.5148" y1="-6.56" x2="4.7148" y2="-4.06" layer="51"/>
<rectangle x1="6.258" y1="-6.56" x2="7.458" y2="-4.06" layer="51"/>
<rectangle x1="9.0012" y1="-6.56" x2="10.2012" y2="-4.06" layer="51"/>
<rectangle x1="-10.6" y1="-4.1" x2="10.6" y2="-2.5" layer="21"/>
</package>
<package name="F15H">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<wire x1="-11.811" y1="17.907" x2="-11.557" y2="17.907" width="0.1524" layer="21"/>
<wire x1="-12.319" y1="17.399" x2="-11.811" y2="17.907" width="0.1524" layer="21" curve="-90"/>
<wire x1="11.684" y1="17.907" x2="12.192" y2="17.399" width="0.1524" layer="21" curve="-90"/>
<wire x1="-11.938" y1="11.684" x2="11.811" y2="11.684" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="7.62" x2="-14.605" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="7.62" x2="-19.685" y2="10.668" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="7.62" x2="-19.685" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="10.668" x2="-19.685" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="11.176" x2="-19.685" y2="11.684" width="0.1524" layer="21"/>
<wire x1="19.558" y1="11.684" x2="19.558" y2="11.176" width="0.1524" layer="21"/>
<wire x1="19.558" y1="11.176" x2="19.558" y2="10.668" width="0.1524" layer="21"/>
<wire x1="19.558" y1="10.668" x2="19.558" y2="7.62" width="0.1524" layer="21"/>
<wire x1="19.558" y1="7.62" x2="19.558" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="11.176" x2="-17.145" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="11.176" x2="-14.605" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="10.668" x2="-14.605" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="10.668" x2="-14.478" y2="10.668" width="0.1524" layer="21"/>
<wire x1="-14.478" y1="8.255" x2="-13.843" y2="7.62" width="0.1524" layer="21" curve="90"/>
<wire x1="-14.605" y1="7.62" x2="-13.716" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-13.716" y1="7.62" x2="-13.462" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-14.478" y1="8.255" x2="-14.478" y2="10.668" width="0.1524" layer="21"/>
<wire x1="-13.462" y1="7.62" x2="-13.462" y2="6.858" width="0.1524" layer="21"/>
<wire x1="-13.462" y1="7.62" x2="13.335" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-13.462" y1="6.858" x2="13.335" y2="6.858" width="0.1524" layer="21"/>
<wire x1="13.335" y1="7.62" x2="13.335" y2="6.858" width="0.1524" layer="21"/>
<wire x1="13.335" y1="7.62" x2="13.589" y2="7.62" width="0.1524" layer="21"/>
<wire x1="13.589" y1="7.62" x2="14.478" y2="7.62" width="0.1524" layer="21"/>
<wire x1="17.018" y1="11.176" x2="19.558" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="11.176" x2="14.478" y2="11.176" width="0.1524" layer="21"/>
<wire x1="14.478" y1="11.176" x2="17.018" y2="11.176" width="0.1524" layer="21"/>
<wire x1="14.478" y1="10.668" x2="14.478" y2="11.176" width="0.1524" layer="21"/>
<wire x1="14.351" y1="8.255" x2="14.351" y2="10.668" width="0.1524" layer="21"/>
<wire x1="14.351" y1="10.668" x2="14.478" y2="10.668" width="0.1524" layer="21"/>
<wire x1="13.716" y1="7.62" x2="14.351" y2="8.255" width="0.1524" layer="21" curve="90"/>
<wire x1="-19.05" y1="-3.175" x2="-19.685" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="-2.54" x2="-19.685" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-14.224" y1="-3.175" x2="-19.05" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="-14.224" y1="-3.175" x2="-13.716" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-13.716" y1="-2.667" x2="-13.716" y2="7.62" width="0.1524" layer="21"/>
<wire x1="13.589" y1="-2.667" x2="13.589" y2="7.62" width="0.1524" layer="21"/>
<wire x1="13.589" y1="-2.667" x2="14.097" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="14.097" y1="-3.175" x2="19.05" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="19.05" y1="-3.175" x2="19.558" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="19.558" y1="-2.667" x2="19.558" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-1.3716" y1="-1.143" x2="-1.3716" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="-6.858" y1="-1.143" x2="-6.858" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="-9.6012" y1="-1.143" x2="-9.6012" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="-8.2296" y1="1.397" x2="-8.2296" y2="2.413" width="0.8128" layer="51"/>
<wire x1="-5.4864" y1="1.397" x2="-5.4864" y2="2.413" width="0.8128" layer="51"/>
<wire x1="0" y1="1.397" x2="0" y2="2.413" width="0.8128" layer="51"/>
<wire x1="4.1148" y1="-1.143" x2="4.1148" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="8.2296" y1="1.397" x2="8.2296" y2="2.413" width="0.8128" layer="51"/>
<wire x1="9.6012" y1="-1.143" x2="9.6012" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="5.4864" y1="1.397" x2="5.4864" y2="2.413" width="0.8128" layer="51"/>
<wire x1="6.858" y1="-1.143" x2="6.858" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="2.7432" y1="1.397" x2="2.7432" y2="2.413" width="0.8128" layer="51"/>
<wire x1="1.3716" y1="-1.143" x2="1.3716" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="-2.7432" y1="1.397" x2="-2.7432" y2="2.413" width="0.8128" layer="51"/>
<wire x1="-4.1148" y1="-1.143" x2="-4.1148" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="14.478" y1="7.62" x2="19.558" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="11.684" x2="-11.938" y2="11.684" width="0.1524" layer="21"/>
<wire x1="-12.319" y1="12.319" x2="-12.319" y2="17.399" width="0.1524" layer="21"/>
<wire x1="-12.954" y1="11.684" x2="-12.319" y2="12.319" width="0.1524" layer="21" curve="90"/>
<wire x1="11.811" y1="11.684" x2="19.558" y2="11.684" width="0.1524" layer="21"/>
<wire x1="12.192" y1="12.319" x2="12.192" y2="17.399" width="0.1524" layer="21"/>
<wire x1="12.192" y1="12.319" x2="12.827" y2="11.684" width="0.1524" layer="21" curve="90"/>
<wire x1="-11.557" y1="17.907" x2="11.43" y2="17.907" width="0.1524" layer="21"/>
<wire x1="11.43" y1="17.907" x2="11.684" y2="17.907" width="0.1524" layer="21"/>
<circle x="-16.6624" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="-16.6624" y="0" radius="2.667" width="0" layer="42"/>
<circle x="-16.6624" y="0" radius="2.667" width="0" layer="43"/>
<circle x="16.6624" y="0" radius="2.667" width="0" layer="42"/>
<circle x="16.6624" y="0" radius="2.667" width="0" layer="43"/>
<circle x="16.6624" y="0" radius="1.651" width="0.1524" layer="21"/>
<pad name="1" x="-9.6012" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-6.858" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-4.1148" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-1.3716" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="1.3716" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="4.1148" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="6.858" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="9.6012" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="-8.2296" y="1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="-5.4864" y="1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="-2.7432" y="1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="0" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="2.7432" y="1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="5.4864" y="1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="8.2296" y="1.27" drill="1.016" shape="octagon"/>
<text x="-19.431" y="-6.35" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-8.382" y="13.97" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="-11.811" y="-1.905" size="1.27" layer="21" ratio="10">1</text>
<text x="11.049" y="-1.905" size="1.27" layer="21" ratio="10">8</text>
<text x="-11.811" y="0.635" size="1.27" layer="21" ratio="10">9</text>
<text x="11.049" y="0.635" size="1.27" layer="21" ratio="10">15</text>
<text x="19.05" y="2.54" size="1.27" layer="21" ratio="10" rot="R90">2,54</text>
<text x="-11.811" y="8.509" size="1.27" layer="21" ratio="10">F15</text>
<rectangle x1="-13.462" y1="6.858" x2="13.335" y2="7.62" layer="21"/>
<rectangle x1="-19.685" y1="11.176" x2="19.558" y2="11.684" layer="21"/>
<rectangle x1="-10.0076" y1="-0.381" x2="-9.1948" y2="6.858" layer="21"/>
<rectangle x1="-8.636" y1="2.159" x2="-7.8232" y2="6.858" layer="21"/>
<rectangle x1="-7.2644" y1="-0.381" x2="-6.4516" y2="6.858" layer="21"/>
<rectangle x1="-5.8928" y1="2.159" x2="-5.08" y2="6.858" layer="21"/>
<rectangle x1="-4.5212" y1="-0.381" x2="-3.7084" y2="6.858" layer="21"/>
<rectangle x1="-3.1496" y1="2.159" x2="-2.3368" y2="6.858" layer="21"/>
<rectangle x1="-1.778" y1="-0.381" x2="-0.9652" y2="6.858" layer="21"/>
<rectangle x1="-0.4064" y1="2.159" x2="0.4064" y2="6.858" layer="21"/>
<rectangle x1="0.9652" y1="-0.381" x2="1.778" y2="6.858" layer="21"/>
<rectangle x1="2.3368" y1="2.159" x2="3.1496" y2="6.858" layer="21"/>
<rectangle x1="3.7084" y1="-0.381" x2="4.5212" y2="6.858" layer="21"/>
<rectangle x1="5.08" y1="2.159" x2="5.8928" y2="6.858" layer="21"/>
<rectangle x1="6.4516" y1="-0.381" x2="7.2644" y2="6.858" layer="21"/>
<rectangle x1="7.8232" y1="2.159" x2="8.636" y2="6.858" layer="21"/>
<rectangle x1="9.1948" y1="-0.381" x2="10.0076" y2="6.858" layer="21"/>
<hole x="-16.6624" y="0" drill="3.302"/>
<hole x="16.6624" y="0" drill="3.302"/>
</package>
<package name="F15HP">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<wire x1="-11.811" y1="17.907" x2="-11.557" y2="17.907" width="0.1524" layer="21"/>
<wire x1="-12.319" y1="17.399" x2="-11.811" y2="17.907" width="0.1524" layer="21" curve="-90"/>
<wire x1="11.684" y1="17.907" x2="12.192" y2="17.399" width="0.1524" layer="21" curve="-90"/>
<wire x1="-11.938" y1="11.684" x2="11.811" y2="11.684" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="7.62" x2="-14.605" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="7.62" x2="-19.685" y2="10.668" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="7.62" x2="-19.685" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="10.668" x2="-19.685" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="11.176" x2="-19.685" y2="11.684" width="0.1524" layer="21"/>
<wire x1="19.558" y1="11.684" x2="19.558" y2="11.176" width="0.1524" layer="21"/>
<wire x1="19.558" y1="11.176" x2="19.558" y2="10.668" width="0.1524" layer="21"/>
<wire x1="19.558" y1="10.668" x2="19.558" y2="7.62" width="0.1524" layer="21"/>
<wire x1="19.558" y1="7.62" x2="19.558" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="11.176" x2="-17.145" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="11.176" x2="-14.605" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="10.668" x2="-14.605" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="10.668" x2="-14.478" y2="10.668" width="0.1524" layer="21"/>
<wire x1="-14.478" y1="8.255" x2="-13.843" y2="7.62" width="0.1524" layer="21" curve="90"/>
<wire x1="-14.605" y1="7.62" x2="-13.716" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-13.716" y1="7.62" x2="-13.462" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-14.478" y1="8.255" x2="-14.478" y2="10.668" width="0.1524" layer="21"/>
<wire x1="-13.462" y1="7.62" x2="-13.462" y2="6.858" width="0.1524" layer="21"/>
<wire x1="-13.462" y1="7.62" x2="13.335" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-13.462" y1="6.858" x2="13.335" y2="6.858" width="0.1524" layer="21"/>
<wire x1="13.335" y1="7.62" x2="13.335" y2="6.858" width="0.1524" layer="21"/>
<wire x1="13.335" y1="7.62" x2="13.589" y2="7.62" width="0.1524" layer="21"/>
<wire x1="13.589" y1="7.62" x2="14.478" y2="7.62" width="0.1524" layer="21"/>
<wire x1="17.018" y1="11.176" x2="19.558" y2="11.176" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="11.176" x2="14.478" y2="11.176" width="0.1524" layer="21"/>
<wire x1="14.478" y1="11.176" x2="17.018" y2="11.176" width="0.1524" layer="21"/>
<wire x1="14.478" y1="10.668" x2="14.478" y2="11.176" width="0.1524" layer="21"/>
<wire x1="14.351" y1="8.255" x2="14.351" y2="10.668" width="0.1524" layer="21"/>
<wire x1="14.351" y1="10.668" x2="14.478" y2="10.668" width="0.1524" layer="21"/>
<wire x1="13.716" y1="7.62" x2="14.351" y2="8.255" width="0.1524" layer="21" curve="90"/>
<wire x1="-19.05" y1="-3.175" x2="-19.685" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="-2.54" x2="-19.685" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-14.224" y1="-3.175" x2="-19.05" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="-14.224" y1="-3.175" x2="-13.716" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-13.716" y1="-2.667" x2="-13.716" y2="7.62" width="0.1524" layer="21"/>
<wire x1="13.589" y1="-2.667" x2="13.589" y2="7.62" width="0.1524" layer="21"/>
<wire x1="13.589" y1="-2.667" x2="14.097" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="14.097" y1="-3.175" x2="19.05" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="19.05" y1="-3.175" x2="19.558" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="19.558" y1="-2.667" x2="19.558" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-1.3716" y1="-1.143" x2="-1.3716" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="-6.858" y1="-1.143" x2="-6.858" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="-9.6012" y1="-1.143" x2="-9.6012" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="-8.2296" y1="1.397" x2="-8.2296" y2="2.413" width="0.8128" layer="51"/>
<wire x1="-5.4864" y1="1.397" x2="-5.4864" y2="2.413" width="0.8128" layer="51"/>
<wire x1="0" y1="1.397" x2="0" y2="2.413" width="0.8128" layer="51"/>
<wire x1="4.1148" y1="-1.143" x2="4.1148" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="8.2296" y1="1.397" x2="8.2296" y2="2.413" width="0.8128" layer="51"/>
<wire x1="9.6012" y1="-1.143" x2="9.6012" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="5.4864" y1="1.397" x2="5.4864" y2="2.413" width="0.8128" layer="51"/>
<wire x1="6.858" y1="-1.143" x2="6.858" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="2.7432" y1="1.397" x2="2.7432" y2="2.413" width="0.8128" layer="51"/>
<wire x1="1.3716" y1="-1.143" x2="1.3716" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="-2.7432" y1="1.397" x2="-2.7432" y2="2.413" width="0.8128" layer="51"/>
<wire x1="-4.1148" y1="-1.143" x2="-4.1148" y2="-0.127" width="0.8128" layer="51"/>
<wire x1="14.478" y1="7.62" x2="19.558" y2="7.62" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="11.684" x2="-11.938" y2="11.684" width="0.1524" layer="21"/>
<wire x1="-12.319" y1="12.319" x2="-12.319" y2="17.399" width="0.1524" layer="21"/>
<wire x1="-12.954" y1="11.684" x2="-12.319" y2="12.319" width="0.1524" layer="21" curve="90"/>
<wire x1="11.811" y1="11.684" x2="19.558" y2="11.684" width="0.1524" layer="21"/>
<wire x1="12.192" y1="12.319" x2="12.192" y2="17.399" width="0.1524" layer="21"/>
<wire x1="12.192" y1="12.319" x2="12.827" y2="11.684" width="0.1524" layer="21" curve="90"/>
<wire x1="-11.557" y1="17.907" x2="11.43" y2="17.907" width="0.1524" layer="21"/>
<wire x1="11.43" y1="17.907" x2="11.684" y2="17.907" width="0.1524" layer="21"/>
<circle x="-16.6624" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="16.6624" y="0" radius="1.651" width="0.1524" layer="21"/>
<pad name="1" x="-9.6012" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-6.858" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-4.1148" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-1.3716" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="1.3716" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="4.1148" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="6.858" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="9.6012" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="-8.2296" y="1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="-5.4864" y="1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="-2.7432" y="1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="0" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="2.7432" y="1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="5.4864" y="1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="8.2296" y="1.27" drill="1.016" shape="octagon"/>
<pad name="G2" x="16.6624" y="0" drill="3.302" diameter="5.08"/>
<pad name="G1" x="-16.6624" y="0" drill="3.302" diameter="5.08"/>
<text x="-19.431" y="-6.35" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-8.382" y="13.97" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="-11.811" y="-1.905" size="1.27" layer="21" ratio="10">1</text>
<text x="11.049" y="-1.905" size="1.27" layer="21" ratio="10">8</text>
<text x="-11.811" y="0.635" size="1.27" layer="21" ratio="10">9</text>
<text x="11.049" y="0.635" size="1.27" layer="21" ratio="10">15</text>
<text x="19.05" y="2.54" size="1.27" layer="21" ratio="10" rot="R90">2,54</text>
<text x="-11.811" y="8.509" size="1.27" layer="21" ratio="10">F15</text>
<rectangle x1="-13.462" y1="6.858" x2="13.335" y2="7.62" layer="21"/>
<rectangle x1="-19.685" y1="11.176" x2="19.558" y2="11.684" layer="21"/>
<rectangle x1="-10.0076" y1="-0.381" x2="-9.1948" y2="6.858" layer="21"/>
<rectangle x1="-8.636" y1="2.159" x2="-7.8232" y2="6.858" layer="21"/>
<rectangle x1="-7.2644" y1="-0.381" x2="-6.4516" y2="6.858" layer="21"/>
<rectangle x1="-5.8928" y1="2.159" x2="-5.08" y2="6.858" layer="21"/>
<rectangle x1="-4.5212" y1="-0.381" x2="-3.7084" y2="6.858" layer="21"/>
<rectangle x1="-3.1496" y1="2.159" x2="-2.3368" y2="6.858" layer="21"/>
<rectangle x1="-1.778" y1="-0.381" x2="-0.9652" y2="6.858" layer="21"/>
<rectangle x1="-0.4064" y1="2.159" x2="0.4064" y2="6.858" layer="21"/>
<rectangle x1="0.9652" y1="-0.381" x2="1.778" y2="6.858" layer="21"/>
<rectangle x1="2.3368" y1="2.159" x2="3.1496" y2="6.858" layer="21"/>
<rectangle x1="3.7084" y1="-0.381" x2="4.5212" y2="6.858" layer="21"/>
<rectangle x1="5.08" y1="2.159" x2="5.8928" y2="6.858" layer="21"/>
<rectangle x1="6.4516" y1="-0.381" x2="7.2644" y2="6.858" layer="21"/>
<rectangle x1="7.8232" y1="2.159" x2="8.636" y2="6.858" layer="21"/>
<rectangle x1="9.1948" y1="-0.381" x2="10.0076" y2="6.858" layer="21"/>
</package>
<package name="F15V">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<wire x1="-11.7094" y1="-2.9464" x2="-12.4968" y2="2.3368" width="0.1524" layer="21"/>
<wire x1="10.414" y1="-3.937" x2="11.7227" y2="-2.905" width="0.1524" layer="21" curve="76.489196"/>
<wire x1="11.176" y1="3.937" x2="12.4915" y2="2.3038" width="0.1524" layer="21" curve="-102.298925"/>
<wire x1="12.4968" y1="2.3114" x2="11.7094" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-11.176" y1="3.937" x2="11.176" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-12.4961" y1="2.3268" x2="-11.176" y2="3.937" width="0.1524" layer="21" curve="-101.30773"/>
<wire x1="-11.7169" y1="-2.9295" x2="-10.414" y2="-3.937" width="0.1524" layer="21" curve="75.428151"/>
<wire x1="-10.414" y1="-3.937" x2="10.414" y2="-3.937" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="-6.223" x2="-16.891" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="-6.223" x2="-14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="-6.096" x2="-14.351" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="-6.096" x2="-14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="-6.223" x2="14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="-6.223" x2="-16.891" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="-5.588" x2="-19.05" y2="-6.223" width="0.1524" layer="21" curve="90"/>
<wire x1="19.05" y1="-6.223" x2="19.685" y2="-5.588" width="0.1524" layer="21" curve="90"/>
<wire x1="19.05" y1="6.223" x2="16.891" y2="6.223" width="0.1524" layer="21"/>
<wire x1="19.685" y1="5.588" x2="19.685" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="19.05" y1="6.223" x2="19.685" y2="5.588" width="0.1524" layer="21" curve="-90"/>
<wire x1="-19.685" y1="5.588" x2="-19.685" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="5.588" x2="-19.05" y2="6.223" width="0.1524" layer="21" curve="-90"/>
<wire x1="14.351" y1="-6.223" x2="14.351" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="14.351" y1="-6.223" x2="16.891" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="14.351" y1="-6.096" x2="16.891" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="16.891" y1="-6.096" x2="16.891" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="16.891" y1="-6.223" x2="19.05" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="14.351" y1="6.223" x2="14.351" y2="6.096" width="0.1524" layer="21"/>
<wire x1="14.351" y1="6.223" x2="-14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="14.351" y1="6.096" x2="16.891" y2="6.096" width="0.1524" layer="21"/>
<wire x1="16.891" y1="6.096" x2="16.891" y2="6.223" width="0.1524" layer="21"/>
<wire x1="16.891" y1="6.223" x2="14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="6.223" x2="-16.891" y2="6.096" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="6.223" x2="-19.05" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="6.096" x2="-14.351" y2="6.096" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="6.096" x2="-14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="6.223" x2="-16.891" y2="6.223" width="0.1524" layer="21"/>
<circle x="16.6624" y="0" radius="2.667" width="0" layer="42"/>
<circle x="16.6624" y="0" radius="2.667" width="0" layer="43"/>
<circle x="-16.6624" y="0" radius="2.667" width="0" layer="42"/>
<circle x="-16.6624" y="0" radius="2.667" width="0" layer="43"/>
<circle x="2.7432" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="4.1148" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="5.4864" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="6.858" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="1.3716" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="0" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-1.3716" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-2.7432" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-4.1148" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-16.6624" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="16.6624" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="9.6012" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="8.2296" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-6.858" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-9.6012" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-5.4864" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-8.2296" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<pad name="1" x="9.6012" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="2" x="6.858" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="3" x="4.1148" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="4" x="1.3716" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="5" x="-1.3716" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="6" x="-4.1148" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="7" x="-6.858" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="8" x="-9.6012" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="9" x="8.2296" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="10" x="5.4864" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="11" x="2.7432" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="12" x="0" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="13" x="-2.7432" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="14" x="-5.4864" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="15" x="-8.2296" y="-1.4224" drill="1.016" shape="octagon"/>
<text x="9.2456" y="2.54" size="0.9906" layer="21" ratio="12">1</text>
<text x="6.4516" y="2.54" size="0.9906" layer="21" ratio="12">2</text>
<text x="3.6576" y="2.54" size="0.9906" layer="21" ratio="12">3</text>
<text x="0.9906" y="2.54" size="0.9906" layer="21" ratio="12">4</text>
<text x="-1.8034" y="2.54" size="0.9906" layer="21" ratio="12">5</text>
<text x="-4.5974" y="2.54" size="0.9906" layer="21" ratio="12">6</text>
<text x="-7.3914" y="2.54" size="0.9906" layer="21" ratio="12">7</text>
<text x="-10.1854" y="2.54" size="0.9906" layer="21" ratio="12">8</text>
<text x="7.8486" y="-3.556" size="0.9906" layer="21" ratio="12">9</text>
<text x="-19.558" y="6.985" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="6.985" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="4.699" y="-3.556" size="0.9906" layer="21" ratio="12">10</text>
<text x="2.032" y="-3.556" size="0.9906" layer="21" ratio="12">11</text>
<text x="-0.762" y="-3.556" size="0.9906" layer="21" ratio="12">12</text>
<text x="-3.556" y="-3.556" size="0.9906" layer="21" ratio="12">13</text>
<text x="-6.35" y="-3.556" size="0.9906" layer="21" ratio="12">14</text>
<text x="-9.017" y="-3.556" size="0.9906" layer="21" ratio="12">15</text>
<hole x="16.6624" y="0" drill="3.302"/>
<hole x="-16.6624" y="0" drill="3.302"/>
</package>
<package name="F15VP">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<wire x1="-11.7094" y1="-2.9464" x2="-12.4968" y2="2.3368" width="0.1524" layer="21"/>
<wire x1="10.414" y1="-3.937" x2="11.7227" y2="-2.905" width="0.1524" layer="21" curve="76.489196"/>
<wire x1="11.176" y1="3.937" x2="12.4915" y2="2.3038" width="0.1524" layer="21" curve="-102.298925"/>
<wire x1="12.4968" y1="2.3114" x2="11.7094" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-11.176" y1="3.937" x2="11.176" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-12.4961" y1="2.3268" x2="-11.176" y2="3.937" width="0.1524" layer="21" curve="-101.30773"/>
<wire x1="-11.7169" y1="-2.9295" x2="-10.414" y2="-3.937" width="0.1524" layer="21" curve="75.428151"/>
<wire x1="-10.414" y1="-3.937" x2="10.414" y2="-3.937" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="-6.223" x2="-16.891" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="-6.223" x2="-14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="-6.096" x2="-14.351" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="-6.096" x2="-14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="-6.223" x2="14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="-6.223" x2="-16.891" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="-5.588" x2="-19.05" y2="-6.223" width="0.1524" layer="21" curve="90"/>
<wire x1="19.05" y1="-6.223" x2="19.685" y2="-5.588" width="0.1524" layer="21" curve="90"/>
<wire x1="19.05" y1="6.223" x2="16.891" y2="6.223" width="0.1524" layer="21"/>
<wire x1="19.685" y1="5.588" x2="19.685" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="19.05" y1="6.223" x2="19.685" y2="5.588" width="0.1524" layer="21" curve="-90"/>
<wire x1="-19.685" y1="5.588" x2="-19.685" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="5.588" x2="-19.05" y2="6.223" width="0.1524" layer="21" curve="-90"/>
<wire x1="14.351" y1="-6.223" x2="14.351" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="14.351" y1="-6.223" x2="16.891" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="14.351" y1="-6.096" x2="16.891" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="16.891" y1="-6.096" x2="16.891" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="16.891" y1="-6.223" x2="19.05" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="14.351" y1="6.223" x2="14.351" y2="6.096" width="0.1524" layer="21"/>
<wire x1="14.351" y1="6.223" x2="-14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="14.351" y1="6.096" x2="16.891" y2="6.096" width="0.1524" layer="21"/>
<wire x1="16.891" y1="6.096" x2="16.891" y2="6.223" width="0.1524" layer="21"/>
<wire x1="16.891" y1="6.223" x2="14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="6.223" x2="-16.891" y2="6.096" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="6.223" x2="-19.05" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="6.096" x2="-14.351" y2="6.096" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="6.096" x2="-14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="6.223" x2="-16.891" y2="6.223" width="0.1524" layer="21"/>
<circle x="2.7432" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="4.1148" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="5.4864" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="6.858" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="1.3716" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="0" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-1.3716" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-2.7432" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-4.1148" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-16.6624" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="16.6624" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="9.6012" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="8.2296" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-6.858" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-9.6012" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-5.4864" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-8.2296" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<pad name="1" x="9.6012" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="2" x="6.858" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="3" x="4.1148" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="4" x="1.3716" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="5" x="-1.3716" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="6" x="-4.1148" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="7" x="-6.858" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="8" x="-9.6012" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="9" x="8.2296" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="10" x="5.4864" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="11" x="2.7432" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="12" x="0" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="13" x="-2.7432" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="14" x="-5.4864" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="15" x="-8.2296" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="G1" x="-16.6624" y="0" drill="3.302" diameter="5.08"/>
<pad name="G2" x="16.6624" y="0" drill="3.302" diameter="5.08"/>
<text x="9.2456" y="2.54" size="0.9906" layer="21" ratio="12">1</text>
<text x="6.4516" y="2.54" size="0.9906" layer="21" ratio="12">2</text>
<text x="3.6576" y="2.54" size="0.9906" layer="21" ratio="12">3</text>
<text x="0.9906" y="2.54" size="0.9906" layer="21" ratio="12">4</text>
<text x="-1.8034" y="2.54" size="0.9906" layer="21" ratio="12">5</text>
<text x="-4.5974" y="2.54" size="0.9906" layer="21" ratio="12">6</text>
<text x="-7.3914" y="2.54" size="0.9906" layer="21" ratio="12">7</text>
<text x="-10.1854" y="2.54" size="0.9906" layer="21" ratio="12">8</text>
<text x="7.8486" y="-3.556" size="0.9906" layer="21" ratio="12">9</text>
<text x="-19.558" y="6.985" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="6.985" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="4.699" y="-3.556" size="0.9906" layer="21" ratio="12">10</text>
<text x="2.032" y="-3.556" size="0.9906" layer="21" ratio="12">11</text>
<text x="-0.762" y="-3.556" size="0.9906" layer="21" ratio="12">12</text>
<text x="-3.556" y="-3.556" size="0.9906" layer="21" ratio="12">13</text>
<text x="-6.35" y="-3.556" size="0.9906" layer="21" ratio="12">14</text>
<text x="-9.017" y="-3.556" size="0.9906" layer="21" ratio="12">15</text>
</package>
<package name="HDF15H">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<wire x1="7.62" y1="-17.607" x2="8.128" y2="-17.099" width="0.1524" layer="21" curve="90"/>
<wire x1="-8.128" y1="-17.099" x2="-7.62" y2="-17.607" width="0.1524" layer="21" curve="90"/>
<wire x1="-15.494" y1="-11.276" x2="-15.494" y2="-7.62" width="0.1524" layer="21"/>
<wire x1="9.614" y1="-10.368" x2="9.614" y2="-11.276" width="0.1524" layer="21"/>
<wire x1="9.614" y1="-10.368" x2="9.487" y2="-10.368" width="0.1524" layer="21"/>
<wire x1="9.487" y1="-10.368" x2="-9.487" y2="-10.368" width="0.1524" layer="21"/>
<wire x1="8.852" y1="-7.62" x2="9.487" y2="-8.255" width="0.1524" layer="21" curve="-90"/>
<wire x1="9.487" y1="-8.255" x2="9.487" y2="-10.368" width="0.1524" layer="21"/>
<wire x1="-9.614" y1="-10.368" x2="-9.614" y2="-11.276" width="0.1524" layer="21"/>
<wire x1="-9.487" y1="-8.255" x2="-9.487" y2="-10.368" width="0.1524" layer="21"/>
<wire x1="-9.487" y1="-10.368" x2="-9.614" y2="-10.368" width="0.1524" layer="21"/>
<wire x1="-9.487" y1="-8.255" x2="-8.852" y2="-7.62" width="0.1524" layer="21" curve="-90"/>
<wire x1="14.859" y1="4.445" x2="15.494" y2="3.81" width="0.1524" layer="21"/>
<wire x1="15.494" y1="3.81" x2="15.494" y2="-11.276" width="0.1524" layer="21"/>
<wire x1="10.033" y1="4.445" x2="14.859" y2="4.445" width="0.1524" layer="21"/>
<wire x1="10.033" y1="4.445" x2="9.525" y2="3.937" width="0.1524" layer="21"/>
<wire x1="9.525" y1="3.937" x2="9.525" y2="-7.62" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="3.937" x2="-9.525" y2="-7.62" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="3.937" x2="-10.033" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-10.033" y1="4.445" x2="-14.986" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-14.986" y1="4.445" x2="-15.494" y2="3.937" width="0.1524" layer="21"/>
<wire x1="-15.494" y1="3.937" x2="-15.494" y2="-7.62" width="0.1524" layer="21"/>
<wire x1="8.128" y1="-11.919" x2="8.128" y2="-17.099" width="0.1524" layer="21"/>
<wire x1="8.128" y1="-11.919" x2="8.763" y2="-11.284" width="0.1524" layer="21" curve="-90"/>
<wire x1="-8.128" y1="-11.919" x2="-8.128" y2="-17.099" width="0.1524" layer="21"/>
<wire x1="-8.763" y1="-11.284" x2="-8.128" y2="-11.919" width="0.1524" layer="21" curve="-90"/>
<wire x1="7.62" y1="-17.607" x2="-7.62" y2="-17.607" width="0.1524" layer="21"/>
<wire x1="15.476" y1="-11.294" x2="-15.38" y2="-11.294" width="0.1524" layer="21"/>
<wire x1="15.475" y1="-7.62" x2="-15.494" y2="-7.62" width="0.1524" layer="21"/>
<circle x="12.5" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="12.5" y="0" radius="2.667" width="0" layer="42"/>
<circle x="12.5" y="0" radius="2.667" width="0" layer="43"/>
<circle x="-12.5" y="0" radius="2.667" width="0" layer="42"/>
<circle x="-12.5" y="0" radius="2.667" width="0" layer="43"/>
<circle x="-12.5" y="0" radius="1.651" width="0.1524" layer="21"/>
<pad name="10" x="-3.672" y="0" drill="0.9"/>
<pad name="9" x="-1.386" y="0" drill="0.9"/>
<pad name="8" x="0.9" y="0" drill="0.9"/>
<pad name="7" x="3.186" y="0" drill="0.9"/>
<pad name="6" x="5.472" y="0" drill="0.9"/>
<pad name="5" x="-4.815" y="2.54" drill="0.9"/>
<pad name="4" x="-2.529" y="2.54" drill="0.9"/>
<pad name="3" x="-0.243" y="2.54" drill="0.9"/>
<pad name="2" x="2.043" y="2.54" drill="0.9"/>
<pad name="1" x="4.329" y="2.54" drill="0.9" shape="octagon"/>
<pad name="15" x="-4.815" y="-2.54" drill="0.9"/>
<pad name="14" x="-2.529" y="-2.54" drill="0.9"/>
<pad name="13" x="-0.243" y="-2.54" drill="0.9"/>
<pad name="12" x="2.043" y="-2.54" drill="0.9"/>
<pad name="11" x="4.329" y="-2.54" drill="0.9"/>
<text x="-8.89" y="5.08" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="0" y="5.08" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="5.48" y="2.095" size="1.27" layer="21" ratio="10">1</text>
<text x="-6.915" y="1.995" size="1.27" layer="21" ratio="10">5</text>
<text x="6.58" y="-0.565" size="1.27" layer="21" ratio="10">6</text>
<text x="-7.115" y="-0.665" size="1.27" layer="21" ratio="10">10</text>
<text x="-7.82" y="-3.565" size="1.27" layer="21" ratio="10">15</text>
<text x="5.98" y="-3.265" size="1.27" layer="21" ratio="10">11</text>
<text x="-6.064" y="-14.717" size="1.27" layer="51" ratio="10">HDF15 CONEC</text>
<text x="2.413" y="-9.652" size="1.27" layer="21">Female</text>
<rectangle x1="0.7" y1="-7.6" x2="1.1" y2="-1.5" layer="21"/>
<rectangle x1="-1.586" y1="-7.6" x2="-1.186" y2="-1.5" layer="21"/>
<rectangle x1="-3.872" y1="-7.6" x2="-3.472" y2="-1.5" layer="21"/>
<rectangle x1="2.986" y1="-7.6" x2="3.386" y2="-1.5" layer="21"/>
<rectangle x1="5.272" y1="-7.6" x2="5.672" y2="-1.5" layer="21"/>
<rectangle x1="-0.443" y1="-7.6" x2="-0.043" y2="-4" layer="21"/>
<rectangle x1="-2.729" y1="-7.6" x2="-2.329" y2="-4" layer="21"/>
<rectangle x1="-5.015" y1="-7.6" x2="-4.615" y2="-4" layer="21"/>
<rectangle x1="1.843" y1="-7.6" x2="2.243" y2="-4" layer="21"/>
<rectangle x1="4.129" y1="-7.6" x2="4.529" y2="-4" layer="21"/>
<rectangle x1="-5.015" y1="-1.6" x2="-4.615" y2="1.5" layer="21"/>
<rectangle x1="-2.729" y1="-1.6" x2="-2.329" y2="1.5" layer="21"/>
<rectangle x1="-0.443" y1="-1.6" x2="-0.043" y2="1.5" layer="21"/>
<rectangle x1="1.843" y1="-1.6" x2="2.243" y2="1.5" layer="21"/>
<rectangle x1="4.129" y1="-1.6" x2="4.529" y2="1.5" layer="21"/>
<hole x="-12.5" y="0" drill="3"/>
<hole x="12.5" y="0" drill="3"/>
</package>
<package name="HDF15V">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<wire x1="-7.409" y1="-3.146" x2="-8.197" y2="2.537" width="0.1524" layer="21"/>
<wire x1="6.876" y1="4.137" x2="8.1915" y2="2.5038" width="0.1524" layer="21" curve="-102.298925"/>
<wire x1="8.197" y1="2.511" x2="7.409" y2="-3.121" width="0.1524" layer="21"/>
<wire x1="-6.876" y1="4.137" x2="6.876" y2="4.137" width="0.1524" layer="21"/>
<wire x1="-8.1961" y1="2.5268" x2="-6.876" y2="4.137" width="0.1524" layer="21" curve="-101.30773"/>
<wire x1="-7.4169" y1="-3.1295" x2="-6.114" y2="-4.137" width="0.1524" layer="21" curve="75.428151"/>
<wire x1="-6.114" y1="-4.137" x2="6.114" y2="-4.137" width="0.1524" layer="21"/>
<wire x1="-15.556" y1="-6.288" x2="-14.921" y2="-6.923" width="0.1524" layer="21" curve="90"/>
<wire x1="14.921" y1="-6.923" x2="15.556" y2="-6.288" width="0.1524" layer="21" curve="90"/>
<wire x1="15.556" y1="6.288" x2="15.556" y2="-6.288" width="0.1524" layer="21"/>
<wire x1="14.921" y1="6.923" x2="15.556" y2="6.288" width="0.1524" layer="21" curve="-90"/>
<wire x1="-15.556" y1="6.288" x2="-15.556" y2="-6.288" width="0.1524" layer="21"/>
<wire x1="-15.556" y1="6.288" x2="-14.921" y2="6.923" width="0.1524" layer="21" curve="-90"/>
<wire x1="-14.913" y1="-6.923" x2="14.921" y2="-6.923" width="0.1524" layer="21"/>
<wire x1="14.913" y1="6.923" x2="-14.921" y2="6.923" width="0.1524" layer="21"/>
<wire x1="6.114" y1="-4.137" x2="7.4169" y2="-3.1295" width="0.1524" layer="21" curve="75.428151"/>
<circle x="12.5" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="12.5" y="0" radius="2.667" width="0" layer="42"/>
<circle x="12.5" y="0" radius="2.667" width="0" layer="43"/>
<circle x="-12.5" y="0" radius="2.667" width="0" layer="42"/>
<circle x="-12.5" y="0" radius="2.667" width="0" layer="43"/>
<circle x="-12.5" y="0" radius="1.651" width="0.1524" layer="21"/>
<pad name="10" x="-3.672" y="0" drill="0.9"/>
<pad name="9" x="-1.386" y="0" drill="0.9"/>
<pad name="8" x="0.9" y="0" drill="0.9"/>
<pad name="7" x="3.186" y="0" drill="0.9"/>
<pad name="6" x="5.472" y="0" drill="0.9"/>
<pad name="5" x="-4.815" y="1.98" drill="0.9"/>
<pad name="4" x="-2.529" y="1.98" drill="0.9"/>
<pad name="3" x="-0.243" y="1.98" drill="0.9"/>
<pad name="2" x="2.043" y="1.98" drill="0.9"/>
<pad name="1" x="4.329" y="1.98" drill="0.9" shape="octagon"/>
<pad name="15" x="-4.815" y="-1.98" drill="0.9"/>
<pad name="14" x="-2.529" y="-1.98" drill="0.9"/>
<pad name="13" x="-0.243" y="-1.98" drill="0.9"/>
<pad name="12" x="2.043" y="-1.98" drill="0.9"/>
<pad name="11" x="4.329" y="-1.98" drill="0.9"/>
<text x="-11.43" y="7.62" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-10.16" y="-6.35" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="5.48" y="1.535" size="1.27" layer="21" ratio="10">1</text>
<text x="-6.915" y="1.435" size="1.016" layer="21" ratio="10">5</text>
<text x="6.58" y="-0.565" size="1.016" layer="21" ratio="10">6</text>
<text x="-7.115" y="-0.665" size="1.016" layer="21" ratio="10">10</text>
<text x="-7.22" y="-3.165" size="1.016" layer="21" ratio="10">15</text>
<text x="5.38" y="-2.705" size="1.016" layer="21" ratio="10">11</text>
<text x="-12.033" y="5.349" size="1.27" layer="51" ratio="10">HDF15 CONEC</text>
<text x="2.413" y="4.826" size="1.27" layer="21">Female</text>
<hole x="-12.5" y="0" drill="3"/>
<hole x="12.5" y="0" drill="3"/>
</package>
<package name="F15VB">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<wire x1="11.7094" y1="2.9464" x2="12.4968" y2="-2.3368" width="0.1524" layer="21"/>
<wire x1="-11.7227" y1="2.905" x2="-10.414" y2="3.937" width="0.1524" layer="21" curve="-76.489196"/>
<wire x1="-12.4915" y1="-2.3038" x2="-11.176" y2="-3.937" width="0.1524" layer="21" curve="102.298925"/>
<wire x1="-12.4968" y1="-2.3114" x2="-11.7094" y2="2.921" width="0.1524" layer="21"/>
<wire x1="11.176" y1="-3.937" x2="-11.176" y2="-3.937" width="0.1524" layer="21"/>
<wire x1="11.176" y1="-3.937" x2="12.4961" y2="-2.3268" width="0.1524" layer="21" curve="101.30773"/>
<wire x1="10.414" y1="3.937" x2="11.7169" y2="2.9295" width="0.1524" layer="21" curve="-75.428151"/>
<wire x1="10.414" y1="3.937" x2="-10.414" y2="3.937" width="0.1524" layer="21"/>
<wire x1="16.891" y1="6.223" x2="16.891" y2="6.096" width="0.1524" layer="21"/>
<wire x1="16.891" y1="6.223" x2="14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="16.891" y1="6.096" x2="14.351" y2="6.096" width="0.1524" layer="21"/>
<wire x1="14.351" y1="6.096" x2="14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="14.351" y1="6.223" x2="-14.351" y2="6.223" width="0.1524" layer="21"/>
<wire x1="19.05" y1="6.223" x2="16.891" y2="6.223" width="0.1524" layer="21"/>
<wire x1="19.05" y1="6.223" x2="19.685" y2="5.588" width="0.1524" layer="21" curve="-90"/>
<wire x1="-19.685" y1="5.588" x2="-19.05" y2="6.223" width="0.1524" layer="21" curve="-90"/>
<wire x1="-19.05" y1="-6.223" x2="-16.891" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="-5.588" x2="-19.685" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="-5.588" x2="-19.05" y2="-6.223" width="0.1524" layer="21" curve="90"/>
<wire x1="19.685" y1="-5.588" x2="19.685" y2="5.588" width="0.1524" layer="21"/>
<wire x1="19.05" y1="-6.223" x2="19.685" y2="-5.588" width="0.1524" layer="21" curve="90"/>
<wire x1="-14.351" y1="6.223" x2="-14.351" y2="6.096" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="6.223" x2="-16.891" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="6.096" x2="-16.891" y2="6.096" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="6.096" x2="-16.891" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="6.223" x2="-19.05" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="-6.223" x2="-14.351" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="-6.223" x2="14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-14.351" y1="-6.096" x2="-16.891" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="-6.096" x2="-16.891" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-16.891" y1="-6.223" x2="-14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="16.891" y1="-6.223" x2="16.891" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="16.891" y1="-6.223" x2="19.05" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="16.891" y1="-6.096" x2="14.351" y2="-6.096" width="0.1524" layer="21"/>
<wire x1="14.351" y1="-6.096" x2="14.351" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="14.351" y1="-6.223" x2="16.891" y2="-6.223" width="0.1524" layer="21"/>
<circle x="-2.7432" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-4.1148" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-5.4864" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-6.858" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-1.3716" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="0" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="1.3716" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="2.7432" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="4.1148" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-9.6012" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="-8.2296" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="6.858" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="9.6012" y="-1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="5.4864" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<circle x="8.2296" y="1.4224" radius="0.762" width="0.254" layer="51"/>
<pad name="1" x="-9.6012" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="2" x="-6.858" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="3" x="-4.1148" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="4" x="-1.3716" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="5" x="1.3716" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="6" x="4.1148" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="7" x="6.858" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="8" x="9.6012" y="-1.4224" drill="1.016" shape="octagon"/>
<pad name="9" x="-8.2296" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="10" x="-5.4864" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="11" x="-2.7432" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="12" x="0" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="13" x="2.7432" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="14" x="5.4864" y="1.4224" drill="1.016" shape="octagon"/>
<pad name="15" x="8.2296" y="1.4224" drill="1.016" shape="octagon"/>
<text x="-9.2456" y="-2.54" size="0.9906" layer="21" ratio="12" rot="R180">1</text>
<text x="-6.4516" y="-2.54" size="0.9906" layer="21" ratio="12" rot="R180">2</text>
<text x="-3.6576" y="-2.54" size="0.9906" layer="21" ratio="12" rot="R180">3</text>
<text x="-0.9906" y="-2.54" size="0.9906" layer="21" ratio="12" rot="R180">4</text>
<text x="1.8034" y="-2.54" size="0.9906" layer="21" ratio="12" rot="R180">5</text>
<text x="4.5974" y="-2.54" size="0.9906" layer="21" ratio="12" rot="R180">6</text>
<text x="7.3914" y="-2.54" size="0.9906" layer="21" ratio="12" rot="R180">7</text>
<text x="10.1854" y="-2.54" size="0.9906" layer="21" ratio="12" rot="R180">8</text>
<text x="-7.8486" y="3.556" size="0.9906" layer="21" ratio="12" rot="R180">9</text>
<text x="-18.288" y="8.255" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="8.255" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="-4.699" y="3.556" size="0.9906" layer="21" ratio="12" rot="R180">10</text>
<text x="-2.032" y="3.556" size="0.9906" layer="21" ratio="12" rot="R180">11</text>
<text x="0.762" y="3.556" size="0.9906" layer="21" ratio="12" rot="R180">12</text>
<text x="3.556" y="3.556" size="0.9906" layer="21" ratio="12" rot="R180">13</text>
<text x="6.35" y="3.556" size="0.9906" layer="21" ratio="12" rot="R180">14</text>
<text x="9.017" y="3.556" size="0.9906" layer="21" ratio="12" rot="R180">15</text>
</package>
<package name="177-015-212-FEMALE">
<description>&lt;b&gt;NorComp 177 Series (0.590" Foorprint)&lt;/b&gt; Female 15 Pol.&lt;p&gt;
Source: Digi-Key, subd.pdf</description>
<wire x1="-12.4079" y1="13.751" x2="-12.9159" y2="13.243" width="0.1524" layer="21" curve="90"/>
<wire x1="12.9159" y1="13.243" x2="12.4079" y2="13.751" width="0.1524" layer="21" curve="90"/>
<wire x1="-13.6779" y1="-11.175" x2="13.6779" y2="-11.175" width="0.1524" layer="21"/>
<wire x1="-19.6469" y1="-5.75" x2="-19.6469" y2="5.115" width="0.1524" layer="21"/>
<wire x1="-19.6469" y1="5.115" x2="-19.6469" y2="7.909" width="0.1524" layer="21"/>
<wire x1="-19.6469" y1="-5.75" x2="-13.6779" y2="-5.75" width="0.1524" layer="21"/>
<wire x1="-13.6779" y1="-5.75" x2="-13.6779" y2="-11.175" width="0.1524" layer="21"/>
<wire x1="13.6779" y1="-11.175" x2="13.6779" y2="-5.75" width="0.1524" layer="21"/>
<wire x1="13.6779" y1="-5.75" x2="19.6469" y2="-5.75" width="0.1524" layer="21"/>
<wire x1="19.6469" y1="-5.75" x2="19.6469" y2="7.909" width="0.1524" layer="21"/>
<wire x1="-19.6469" y1="7.909" x2="19.6469" y2="7.909" width="0.1524" layer="21"/>
<wire x1="12.9159" y1="8.544" x2="12.9159" y2="13.243" width="0.1524" layer="21"/>
<wire x1="13.5509" y1="7.909" x2="12.9159" y2="8.544" width="0.1524" layer="21" curve="-90"/>
<wire x1="-12.9159" y1="8.544" x2="-12.9159" y2="13.243" width="0.1524" layer="21"/>
<wire x1="-12.9159" y1="8.544" x2="-13.5509" y2="7.909" width="0.1524" layer="21" curve="-90"/>
<wire x1="-12.4079" y1="13.751" x2="12.4079" y2="13.751" width="0.1524" layer="21"/>
<wire x1="-19.6469" y1="5.115" x2="19.6469" y2="5.115" width="0.1524" layer="21"/>
<wire x1="13.6779" y1="-5.587" x2="13.6779" y2="4.918" width="0.1524" layer="21"/>
<wire x1="-13.6779" y1="4.918" x2="-13.6779" y2="-5.587" width="0.1524" layer="21"/>
<circle x="-16.6751" y="0" radius="1.651" width="0.1524" layer="21"/>
<circle x="16.6751" y="0" radius="1.651" width="0.1524" layer="21"/>
<pad name="5" x="1.3843" y="-9.8401" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="4" x="-1.3843" y="-9.8401" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="3" x="-4.1529" y="-9.8401" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="2" x="-6.9215" y="-9.8401" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="1" x="-9.6901" y="-9.8401" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="9" x="-8.3058" y="-6.9965" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="6" x="4.1529" y="-9.8401" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="7" x="6.9215" y="-9.8401" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="8" x="9.6901" y="-9.8401" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="10" x="-5.5372" y="-6.9965" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="11" x="-2.7686" y="-6.9965" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="12" x="0" y="-6.9965" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="13" x="2.7686" y="-6.9965" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="14" x="5.5372" y="-6.9965" drill="1.1938" diameter="1.524" shape="octagon"/>
<pad name="15" x="8.3058" y="-6.9965" drill="1.1938" diameter="1.524" shape="octagon"/>
<text x="13.0429" y="-11.43" size="1.778" layer="25" ratio="10" rot="R180">&gt;NAME</text>
<text x="11.7729" y="-1.27" size="1.778" layer="27" ratio="10" rot="R180">&gt;VALUE</text>
<text x="11.7729" y="-8.895" size="1.27" layer="21" ratio="10" rot="R180">8</text>
<text x="-11.3919" y="-8.895" size="1.27" layer="21" ratio="10" rot="R180">1</text>
<text x="-11.3919" y="-6.355" size="1.27" layer="21" ratio="10" rot="R180">9</text>
<text x="11.7729" y="-6.228" size="1.27" layer="21" ratio="10" rot="R180">15</text>
</package>
</packages>
<symbols>
<symbol name="FV">
<wire x1="0.889" y1="0.889" x2="0.889" y2="-0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<text x="1.27" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="1.397" size="1.778" layer="96">&gt;VALUE</text>
<pin name="F" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="F">
<wire x1="0.889" y1="0.889" x2="0.889" y2="-0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<text x="1.27" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<pin name="F" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="F15?S" prefix="X" uservalue="yes">
<description>&lt;b&gt;SUB-D&lt;/b&gt;</description>
<gates>
<gate name="-1" symbol="FV" x="0" y="0" addlevel="always"/>
<gate name="-2" symbol="F" x="0" y="-2.54" addlevel="always"/>
<gate name="-3" symbol="F" x="0" y="-5.08" addlevel="always"/>
<gate name="-4" symbol="F" x="0" y="-7.62" addlevel="always"/>
<gate name="-5" symbol="F" x="0" y="-10.16" addlevel="always"/>
<gate name="-6" symbol="F" x="0" y="-12.7" addlevel="always"/>
<gate name="-7" symbol="F" x="0" y="-15.24" addlevel="always"/>
<gate name="-8" symbol="F" x="0" y="-17.78" addlevel="always"/>
<gate name="-9" symbol="F" x="0" y="-20.32" addlevel="always"/>
<gate name="-10" symbol="F" x="0" y="-22.86" addlevel="always"/>
<gate name="-11" symbol="F" x="0" y="-25.4" addlevel="always"/>
<gate name="-12" symbol="F" x="0" y="-27.94" addlevel="always"/>
<gate name="-13" symbol="F" x="0" y="-30.48" addlevel="always"/>
<gate name="-14" symbol="F" x="0" y="-33.02" addlevel="always"/>
<gate name="-15" symbol="F" x="0" y="-35.56" addlevel="always"/>
</gates>
<devices>
<device name="D" package="F15D">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="H" package="F15H">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HP" package="F15HP">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="V" package="F15V">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="VP" package="F15VP">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HDH" package="HDF15H">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HDV" package="HDF15V">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="VB" package="F15VB">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name=".590" package="177-015-212-FEMALE">
<connects>
<connect gate="-1" pin="F" pad="1"/>
<connect gate="-10" pin="F" pad="10"/>
<connect gate="-11" pin="F" pad="11"/>
<connect gate="-12" pin="F" pad="12"/>
<connect gate="-13" pin="F" pad="13"/>
<connect gate="-14" pin="F" pad="14"/>
<connect gate="-15" pin="F" pad="15"/>
<connect gate="-2" pin="F" pad="2"/>
<connect gate="-3" pin="F" pad="3"/>
<connect gate="-4" pin="F" pad="4"/>
<connect gate="-5" pin="F" pad="5"/>
<connect gate="-6" pin="F" pad="6"/>
<connect gate="-7" pin="F" pad="7"/>
<connect gate="-8" pin="F" pad="8"/>
<connect gate="-9" pin="F" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="X1" library="con-subd" deviceset="F15?S" device="HDV"/>
<part name="AGND5" library="supply1" deviceset="AGND" device=""/>
<part name="X2" library="con-subd" deviceset="F15?S" device="D"/>
<part name="AGND1" library="supply1" deviceset="AGND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="X1" gate="-1" x="193.04" y="187.96" rot="MR0"/>
<instance part="X1" gate="-2" x="193.04" y="185.42" rot="MR0"/>
<instance part="X1" gate="-3" x="193.04" y="182.88" rot="MR0"/>
<instance part="X1" gate="-4" x="119.38" y="147.32"/>
<instance part="X1" gate="-5" x="119.38" y="144.78"/>
<instance part="X1" gate="-6" x="119.38" y="142.24"/>
<instance part="X1" gate="-7" x="119.38" y="139.7"/>
<instance part="X1" gate="-8" x="119.38" y="137.16"/>
<instance part="X1" gate="-9" x="193.04" y="167.64" rot="MR0"/>
<instance part="X1" gate="-10" x="193.04" y="165.1" rot="MR0"/>
<instance part="X1" gate="-11" x="193.04" y="162.56" rot="MR0"/>
<instance part="X1" gate="-12" x="193.04" y="160.02" rot="MR0"/>
<instance part="X1" gate="-13" x="193.04" y="157.48" rot="MR0"/>
<instance part="X1" gate="-14" x="193.04" y="154.94" rot="MR0"/>
<instance part="X1" gate="-15" x="193.04" y="152.4" rot="MR0"/>
<instance part="AGND5" gate="VR1" x="114.3" y="129.54"/>
<instance part="X2" gate="-1" x="200.66" y="187.96"/>
<instance part="X2" gate="-2" x="200.66" y="185.42"/>
<instance part="X2" gate="-3" x="200.66" y="182.88"/>
<instance part="X2" gate="-4" x="200.66" y="180.34"/>
<instance part="X2" gate="-5" x="200.66" y="177.8"/>
<instance part="X2" gate="-6" x="200.66" y="175.26"/>
<instance part="X2" gate="-7" x="200.66" y="172.72"/>
<instance part="X2" gate="-8" x="200.66" y="170.18"/>
<instance part="X2" gate="-9" x="200.66" y="167.64"/>
<instance part="X2" gate="-10" x="200.66" y="165.1"/>
<instance part="X2" gate="-11" x="200.66" y="162.56"/>
<instance part="X2" gate="-12" x="200.66" y="160.02"/>
<instance part="X2" gate="-13" x="200.66" y="157.48"/>
<instance part="X2" gate="-14" x="200.66" y="154.94"/>
<instance part="X2" gate="-15" x="200.66" y="152.4"/>
<instance part="AGND1" gate="VR1" x="182.88" y="170.18"/>
</instances>
<busses>
</busses>
<nets>
<net name="AGND" class="0">
<segment>
<pinref part="X1" gate="-8" pin="F"/>
<pinref part="AGND5" gate="VR1" pin="AGND"/>
<wire x1="116.84" y1="137.16" x2="114.3" y2="137.16" width="0.1524" layer="91"/>
<wire x1="114.3" y1="137.16" x2="114.3" y2="132.08" width="0.1524" layer="91"/>
<pinref part="X1" gate="-7" pin="F"/>
<wire x1="116.84" y1="139.7" x2="114.3" y2="139.7" width="0.1524" layer="91"/>
<wire x1="114.3" y1="139.7" x2="114.3" y2="137.16" width="0.1524" layer="91"/>
<junction x="114.3" y="137.16"/>
<pinref part="X1" gate="-6" pin="F"/>
<wire x1="116.84" y1="142.24" x2="114.3" y2="142.24" width="0.1524" layer="91"/>
<wire x1="114.3" y1="142.24" x2="114.3" y2="139.7" width="0.1524" layer="91"/>
<junction x="114.3" y="139.7"/>
<pinref part="X1" gate="-5" pin="F"/>
<wire x1="116.84" y1="144.78" x2="114.3" y2="144.78" width="0.1524" layer="91"/>
<wire x1="114.3" y1="144.78" x2="114.3" y2="142.24" width="0.1524" layer="91"/>
<junction x="114.3" y="142.24"/>
</segment>
<segment>
<pinref part="X2" gate="-5" pin="F"/>
<wire x1="198.12" y1="177.8" x2="193.04" y2="177.8" width="0.1524" layer="91"/>
<wire x1="193.04" y1="177.8" x2="193.04" y2="175.26" width="0.1524" layer="91"/>
<pinref part="X2" gate="-8" pin="F"/>
<wire x1="193.04" y1="175.26" x2="193.04" y2="172.72" width="0.1524" layer="91"/>
<wire x1="193.04" y1="172.72" x2="193.04" y2="170.18" width="0.1524" layer="91"/>
<wire x1="193.04" y1="170.18" x2="198.12" y2="170.18" width="0.1524" layer="91"/>
<pinref part="X2" gate="-7" pin="F"/>
<wire x1="198.12" y1="172.72" x2="193.04" y2="172.72" width="0.1524" layer="91"/>
<junction x="193.04" y="172.72"/>
<pinref part="X2" gate="-6" pin="F"/>
<wire x1="198.12" y1="175.26" x2="193.04" y2="175.26" width="0.1524" layer="91"/>
<junction x="193.04" y="175.26"/>
<wire x1="193.04" y1="177.8" x2="182.88" y2="177.8" width="0.1524" layer="91"/>
<wire x1="182.88" y1="177.8" x2="182.88" y2="172.72" width="0.1524" layer="91"/>
<junction x="193.04" y="177.8"/>
<pinref part="AGND1" gate="VR1" pin="AGND"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="X2" gate="-1" pin="F"/>
<pinref part="X1" gate="-1" pin="F"/>
<wire x1="195.58" y1="187.96" x2="198.12" y2="187.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="X2" gate="-2" pin="F"/>
<pinref part="X1" gate="-2" pin="F"/>
<wire x1="195.58" y1="185.42" x2="198.12" y2="185.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="X2" gate="-3" pin="F"/>
<pinref part="X1" gate="-3" pin="F"/>
<wire x1="195.58" y1="182.88" x2="198.12" y2="182.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="X2" gate="-13" pin="F"/>
<pinref part="X1" gate="-13" pin="F"/>
<wire x1="195.58" y1="157.48" x2="198.12" y2="157.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="X2" gate="-14" pin="F"/>
<pinref part="X1" gate="-14" pin="F"/>
<wire x1="195.58" y1="154.94" x2="198.12" y2="154.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="X2" gate="-15" pin="F"/>
<pinref part="X1" gate="-15" pin="F"/>
<wire x1="195.58" y1="152.4" x2="198.12" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="X2" gate="-9" pin="F"/>
<pinref part="X1" gate="-9" pin="F"/>
<wire x1="195.58" y1="167.64" x2="198.12" y2="167.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="X2" gate="-10" pin="F"/>
<pinref part="X1" gate="-10" pin="F"/>
<wire x1="195.58" y1="165.1" x2="198.12" y2="165.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="X2" gate="-11" pin="F"/>
<pinref part="X1" gate="-11" pin="F"/>
<wire x1="195.58" y1="162.56" x2="198.12" y2="162.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="X2" gate="-12" pin="F"/>
<pinref part="X1" gate="-12" pin="F"/>
<wire x1="195.58" y1="160.02" x2="198.12" y2="160.02" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
