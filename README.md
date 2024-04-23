This Project Comes From Some Videos I've Seen Of Noise Being Made From Code Using Physics Engines. With My Previous Projects NewFound Ideas I Try To Implement Audio Drivers And Sample Buffers Using The Windows API. I Have Been Also Using This Project
As An Opportunity To Learn More About GitHub And Really How To Use It Alongside IDEs (In My Case Visual Studio) As Its Allowed Me A Much Easier Documentation And Improvement Of Code Without Having To Update The GitHub Page With A Whole New File Dump. I Will Try To
Use This In Further Improvements Of Previous Repos As Is Super Dope. <img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/f9c6103e-0226-4364-9018-6a9e1f816578" alt="Cornstarch <3" width="35" height="29">

------------------------------------------------------

<img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/d2377047-3dfa-4bba-9def-8668d01f8517" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/d2377047-3dfa-4bba-9def-8668d01f8517" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/d2377047-3dfa-4bba-9def-8668d01f8517" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/d2377047-3dfa-4bba-9def-8668d01f8517" alt="Cornstarch <3" width="55" height="49">

**The Breakdown:**

This Program Deep Down Is Working On Circles And A Audio Driver Through A OpenGL GLSL Window.

Collisions On A Circle Will Call The Audio Driver To Make A Sound Based Upon The Circles Velocity. Both Parts Have Been Implemented To Try To Encapsulate A Pretty Broad Reach Of Inherit Abilities That Will Be Expanded Upon.

The Program Will Initialize A GLSL Window In Which Will Be Using OpenGL To Render Circles On The Screen. 

During Initialization, We Will Look At Our Global Variable Amount Of Spawned Circles And Will Spawn The According Amount In A Pre-Defined Range In The Window (In Our Case Inside The Boundary Circle). Each Spawned Circle Will 
Also Get A Pseudo-Random Velocity.

The Circles Will Have A Dynamic Radius, Velocity, As Well As Color And Segment Count (For Circles Drawn With Many Very Small Individual Lines. In A Newer Version We Will Have Variable Pitch And Pitch Time To Be Supplied). These Circles Will Move Along Their Velocity Vector Until A Collision Happens In Which They Will Redirect, Going Along The Same Velocity Vector But In The Opposite Way With Some Addition Of The Velocity From A Pseudo Force To Accelerate The Ball. At Every Collision, They Will Call Upon A Defined Audio_Driver Class, In Which Uses Multi-threading To Execute A Detached Thread For The Audio Call Function. This Class Audio Driver Will Declare Formatting Requirements For The Audio Header Buffer As Well As Formatting Of Our Audio API Connection For This Detached Threads Execution.

<img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/3861a441-5761-4674-a8ad-642c9d733942" alt="Your GIF Description" width="185" height="115">

When The Audio_Driver Is Called, It Will Make A "Thud" Sound At A Given Pitch Defined By The Current Velocity Of The Given Circle.
In This Branch, We Are Stuck In A Circle-Boundary In Which Will Give A More Broad Range Of Interactions Compared To The Window Borders. In Future Installations, We Will Want To Have The Ability To Free-Hand Draw The Collidable Area.


The Main Purpose Of This Program Is To Hear The Interesting Sounds That Come From Computers When Subject To A Certain Variable Environment. This Project Has Shown Interesting Behaivor While Being Quite Trivial In Perspective (Collision Go Bonk) As It Allows Me To Simulate Many Balls And THeir Collisions In Dynamic Environments Of My Specieified Variability.

Project Has Taught Me A Lot About MultiThreading As Well As How Audio Is Actually Called Upon To The OS Driver And Just Why It Can Be Seen As A Normal Issue For Many Programs As Properly Defining Formats And Sizes Was A Little Challenging. Still Have Issues But Starting To Understand It More.
I Also Am Learning About More Ways To Call Draw Calls On The OpenGL API Other Than Triangles.<img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/4e382c5b-bf2d-4834-80e5-fd4227b9902e" alt="Cornstarch <3" width="35" height="29">


<img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/63200c18-e940-46f2-aa56-fcf2f2a5893c" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/63200c18-e940-46f2-aa56-fcf2f2a5893c" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/63200c18-e940-46f2-aa56-fcf2f2a5893c" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/63200c18-e940-46f2-aa56-fcf2f2a5893c" alt="Cornstarch <3" width="55" height="49">

------------------------------------------------------

<img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/0a564bb7-d4b0-4e7f-afe5-ae799e0b575a" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/0a564bb7-d4b0-4e7f-afe5-ae799e0b575a" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/0a564bb7-d4b0-4e7f-afe5-ae799e0b575a" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/0a564bb7-d4b0-4e7f-afe5-ae799e0b575a" alt="Cornstarch <3" width="55" height="49">

**Features:**

**Newest Addition, Waveform Visualization:**
![SINGLE_BALL-ezgif com-video-to-gif-converter](https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/1f06e60f-041b-47ae-8f58-39251609418a)

![MULTIPLE_BALLS-ezgif com-video-to-gif-converter (1)](https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/f0078bc3-ef16-460e-93fe-f75362144df1)

**Snapshot Of Window And Waveform Visualization (Newer Version With More Customized Waveform Color Palette):**
<img width="900" alt="image" src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/80cec64f-7f15-4c6a-80e0-c5966eb68a1e">

**User-Variable Constants (Like Ball Count):**
![2024-04-0222-22-01-ezgif com-video-to-gif-converter](https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/bddf1d6d-32ac-4ad1-b6fe-9143d6f8d670)


<img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/b28fd612-824f-48f5-a2dd-c46f8824b07e" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/b28fd612-824f-48f5-a2dd-c46f8824b07e" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/b28fd612-824f-48f5-a2dd-c46f8824b07e" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_BouncingBalls_WindowsAudioAPI/assets/76754592/b28fd612-824f-48f5-a2dd-c46f8824b07e" alt="Cornstarch <3" width="55" height="49">

