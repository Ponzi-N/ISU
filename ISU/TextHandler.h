#include "FontHandler.h"
#include "FontShader.h"
#include "pColour.h"

class TextClass
{
private:
	struct pString
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		int red, green, blue;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);

	bool SetFps(int, ID3D11DeviceContext*);
	bool SetCpu(int, ID3D11DeviceContext*);

private:
	bool InitializeSentence(pString**, int, ID3D11Device*);
	bool UpdateSentence(pString*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(pString**);
	bool RenderSentence(ID3D11DeviceContext*, pString*, D3DXMATRIX, D3DXMATRIX);

private:
	FontClass* pFont;
	FontShaderClass* pFontShader;
	int ScreenWidth, ScreenHeight;
	D3DXMATRIX pBaseViewMatrix;
	pString* m_sentence1;
	pString* m_sentence2;
};