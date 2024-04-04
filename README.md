This Project Comes From Some Videos I've Seen Of Noise Being Made From Code Using Physics Engines. With My Previous Projects NewFound Ideas I Try To Implement Audio Drivers And Sample Buffers Using The Windows API. I Have Been Also Using This Project
As An Opportunity To Learn More About GitHub And Really How To Use It Alongside IDEs (In My Case Visual Studio) As Its Allowed Me A Much Easier Documentation And Improvement Of Code Without Having To Update The GitHub Page With A Whole New File Dump. I Will Try To
Use This In Further Improvements Of Previous Repos As Is Super Dope.<img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/f9c6103e-0226-4364-9018-6a9e1f816578" alt="Cornstarch <3" width="35" height="29">

The Program Will Initialize A GLSL Window In Which Will Be Using OpenGL To Render Circles On The Screen. The Circles Will Have A Dynamic Radius, Velocity, As Well As Color And Segment Count (For Circles Drawn With Many Very Small Individual Lines. In A Newer Version We Will Have Variable
Pitch And Pitch Time To Be Supplied. 
These Circles Will Move Along Their Velocity Vector Until A Collision Happens In Which They Will Redirect, Going Along The Same Velocity Vector But In The Opposite Way With Some Removal Of The Velocity From A Pseudo Frictional Force. At Every Collision, They Will Call Upon A Defined Audio_Driver
Class, In Which Uses Multi-threading To Execute Many Audio Write Calls. This Class Will Declare Formatting Requirements For The Audio Header Buffer As Well As Formatting Of Our Audio API Connection. 

<img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/3861a441-5761-4674-a8ad-642c9d733942" alt="Your GIF Description" width="185" height="115">


When The Audio_Driver Is Called, It Will Make A "Thud" Sound At A Given Pitch Defined By The Current Velocity Of The Given Circle.
In This Branch, We Are Stuck In A Circle-Boundary In Which Will Give A More Broad Range Of Interactions Compared To The Window Borders. In Future Installations, We Will Want To Have The Ability To Free-Hand Draw The Collidable Area.

![2024-04-0222-22-01-ezgif com-video-to-gif-converter](https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/bddf1d6d-32ac-4ad1-b6fe-9143d6f8d670)

Project Has Taught Me A Lot About MultiThreading As Well As How Audio Is Actually Called Upon To The OS Driver And Just Why It Can Be Seen As A Normal Issue For Many Programs As Properly Defining Formats And Sizes Was A Little Challenging. Still Have Issues But Starting To Understand It More.
I Also Am Learning About More Ways To Call Draw Calls On The OpenGL API Other Than Triangles.
