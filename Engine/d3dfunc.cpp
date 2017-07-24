#include "DarkSDK.h"
#include "d3d9.h"


#define D3D_FVF_2D_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct TransformedVertex	// D3D_FVF_2D_VERTEX
{
	float x, y, z, w;		// Position of vertex in 3D space
    DWORD color;			// Color of vertex
};


int							g_nRed=255;
int							g_nGreen=255;
int							g_nBlue=255;
int							g_nAlpha=255;
int							g_nFontSize;
bool						g_Bold = false;
bool						g_Italic = false;
char						g_strFont[LF_FACESIZE];
ID3DXFont*					g_pFont[20];
ID3DXFont*					g_pFont2 = NULL;
ID3DXFont*					g_pStatsFont = NULL;
IDirect3DDevice9*			g_pd3dDevice = NULL;
ID3DXSprite*				g_pTextSprite = NULL;

void InitD3DFunc() {
	g_pd3dDevice = dbGetDirect3DDevice();
}

void d3d_dot (int x1,int y1, int r, int g, int b, int a) {
	TransformedVertex *pVertices = NULL;
	TransformedVertex g_lineList[] = 
	{
		{-1.0f,  0.0f, 0.0f, 1.0f, D3DCOLOR_ARGB( 255, 255, 0, 255 ) }, // Line #1
	};

	g_lineList[0].x=(float)x1;
	g_lineList[0].y=(float)y1;
	g_lineList[0].z=1.0f;
	g_lineList[0].color=D3DCOLOR_ARGB( a, r, g, b );



	g_pd3dDevice->SetTexture(0,NULL);
	g_pd3dDevice->SetTexture(1,NULL);
	g_pd3dDevice->SetVertexShader(NULL);
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	g_pd3dDevice->SetFVF( D3D_FVF_2D_VERTEX );
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	g_pd3dDevice->DrawPrimitiveUP(D3DPT_POINTLIST,1,g_lineList,sizeof(TransformedVertex));


}
void InitText() {
	g_pd3dDevice = dbGetDirect3DDevice();
}

void SetTextCol(int r, int g, int b, int a) {
	g_nRed = r;
	g_nGreen = g;
	g_nBlue = b;
	g_nAlpha = a;
}

void SetFont(int nFont, LPSTR pFont, int nFontSize, int nFontBold, int nFontItalic) {
    HRESULT hr;

    if (nFont > 20)	{
		return;
	}

	HDC hDC = GetDC(NULL);

    int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
    ReleaseDC(NULL, hDC);

    int g_nFontSize = -nFontSize * nLogPixelsY / 72;

	if (nFont == 1)
		lstrcpy(g_strFont, pFont);

	if (nFontBold == 1)	{
		g_Bold = true;
	} else {
		g_Bold = false;
	}

	if (nFontItalic == 1) {
		g_Italic = true;
	} else {
		g_Italic = false;
	}

    hr = D3DXCreateFont( g_pd3dDevice,					// D3D device
                         g_nFontSize,				    // Height
                         0,								// Width
                         g_Bold ? FW_BOLD : FW_NORMAL,  // Weight
                         1,								// MipLevels, 0 = autogen mipmaps
                         g_Italic,						// Italic
                         DEFAULT_CHARSET,				// CharSet
                         OUT_DEFAULT_PRECIS,			// OutputPrecision
                         DEFAULT_QUALITY,				// Quality
                         DEFAULT_PITCH | FF_DONTCARE,	// PitchAndFamily
                         pFont,							// pFaceName
                         &g_pFont[nFont]);              // ppFont

	g_pFont[nFont]->PreloadGlyphs(32,180);

	if (g_pTextSprite == NULL)
		hr = D3DXCreateSprite( g_pd3dDevice, &g_pTextSprite );

}


void StartText(void) {
	g_pTextSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
}

void EndText(void) {
	g_pTextSprite->End();
}

void AAText(int nFont, int x, int y, int nAlign, LPSTR pString) {
    RECT rc;

    if (nFont > 20)
		return;
	
    SetRect(&rc, x, y, 0, 0 );

    switch (nAlign) {
		case 1:
		{
			g_pFont[nFont]->DrawText( g_pTextSprite, pString, -1, &rc, DT_CALCRECT, D3DCOLOR_ARGB( g_nAlpha, g_nRed, g_nGreen, g_nBlue ));
			rc.left=x-((rc.right-x)/2);
			rc.right=x+((rc.right-x)/2);
			break;
		}

		case 2:
		{
			g_pFont[nFont]->DrawText( g_pTextSprite, pString, -1, &rc, DT_CALCRECT, D3DCOLOR_ARGB( g_nAlpha, g_nRed, g_nGreen, g_nBlue ));
			rc.left=x-(rc.right-x);
			rc.right=x+(rc.right-x);
			break;
		}
	}

	g_pFont[nFont]->DrawText( g_pTextSprite, pString, -1, &rc, DT_NOCLIP, D3DCOLOR_ARGB( g_nAlpha, g_nRed, g_nGreen, g_nBlue ));
}
