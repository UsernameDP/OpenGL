## SSBO
- std140 (and latest versions) was designed for hardware where **vec4** was the smallest addressable unit. 
In other words, **vec3 is just a vec4 with an unused last index under the hood**. So, if you are going to upload
any other vector other than vec4, you must upload a vec4 instead of a vec3 or vec2. 
- Uploading no *vec* like float, uint, and int causes no problems. 
- If you upload a *vec* with float or any other primitives, you will encounter some problems with bytes.
