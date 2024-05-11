    #shader vertex
    #version 330 core
    
    layout(location=0) in vec4 position;
    layout(location=1) in vec4 color;
    layout(location=2) in vec2 texCoord;
    layout(location=3) in float texIndex;
    
    out vec4 v_Color;
    out vec2 v_TexCoord;
    out float v_TexIdx;

    uniform mat4 u_MVP;

    void main()
    {
       v_Color = color;
       gl_Position = position;
       v_TexCoord = texCoord;
       v_TexIdx = texIndex;
    };

    #shader fragment
    #version 330 core

    uniform vec4 u_Color;
    uniform sampler2D u_Texture;
    
    layout(location=0) out vec4 color;
    
    in vec4 v_Color;
    in vec2 v_TexCoord;
    in float v_TexIdx;

    uniform sampler2D u_Textures[2];

    void main()
    {
       int index = int(v_TexIdx);
       color = texture(u_Textures[index], v_TexCoord);
    };