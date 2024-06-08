This code is my attempt to simulate PEPITES beam profiler using GEANT4. It consists of two ionization chamber like configuration with oposing electric field one another. The protons move from one side of the profiler hiting nanometer thickness gold-layered kapton that creates secondary particle. The secondary particle will move due to electrical field toward the opposite gold-layered kapton that are segmented. 

<p align="center">
  <img src="https://github.com/Feryalchemist/GEANT4-Beam-Profiler-Example/blob/main/Image/Screenshot%20from%202024-06-08%2023-19-26.png?raw=true" alt="Coincidence"/>
</p>

The simulation visualization is shown above, where the proton (thin blue line) is generated at the face of the profiler towards z- direction. The geometry is in wireframe view, where the green is Kapton and maroon is Gold layer/electrode. The large arrow shows the electric field. The secondary particle will be attracted to the field, thus it could be counted by the segmented electrode.

One chamber has x axis segmented electrode while the other has y axis segmented electrode. The coincidence between combination of two chambers' segment will map the particle intensity on those lateral section. It would be implemented like the image below:

<p align="center">
  <img src="https://github.com/Feryalchemist/GEANT4-Beam-Profiler-Example/blob/main/Image/CoincidenceLine.png?raw=true" alt="Coincidence"/>
</p>

In this image, the x and y segment are simplified into 6x6 segment. The beam particle that pass through in red point's area is counted using the logic gate on the right side. The secondary particle created by the beam could scatter to or received the scatter from other X's segment or Y's segment, thus create false positive counts. The XOR gate array only allow the unique signal from $X_{1}$'s segment and $Y_{1}$'s, where the red point's area is. The shown gate is the only case to account the count in red point's area.  


references:

1. https://accelconf.web.cern.ch/ibic2022/papers/mop21.pdf
2. https://www.sciencedirect.com/science/article/pii/S0168583X20300045
