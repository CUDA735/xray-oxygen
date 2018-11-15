#include "common.h"
#include "lmodel.h"

#ifdef USE_MINMAX_SM
#define SM_MINMAX
#endif

#if SUN_QUALITY>2
#define ULTRA_SHADOWS_ON
#endif //	SUN_QUALITY>2

#ifdef ULTRA_SHADOWS_ON
#define USE_ULTRA_SHADOWS
#endif

#include "shadow.h"
uniform float3	view_shadow_proj;


#ifdef USE_SUNFILTER
#ifdef MSAA_OPTIMIZATION
float4 main ( v2p_volume I, uint iSample : SV_SAMPLEINDEX  ) : SV_Target
#else
float4 main ( v2p_volume I  ) : SV_Target
#endif
{
	//float4 _P = tex2D( s_position, tc );

	gbuffer_data gbd = gbuffer_load_data( GLD_P(I.tc, I.hpos, ISAMPLE) );

#ifdef	GBUFFER_OPTIMIZATION
	//	Emulate virtual offset
	gbd.P += gbd.N*0.015f;
#endif	//	GBUFFER_OPTIMIZATION

	float4 _P = float4( gbd.P, 1.f);

	float4 PS = mul( m_shadow,  _P );

	float s	= shadowtest_sun( PS, I.tcJ ) * sunmask( _P );

	return s;
}
#else
#ifdef MSAA_OPTIMIZATION
float4 main ( v2p_volume I,  uint iSample : SV_SAMPLEINDEX ) : SV_Target
#else
float4 main ( v2p_volume I ) : SV_Target
#endif
{
	//float4 	_P	= tex2D( s_position, tc );
	//float4	_N	= tex2D( s_normal, tc );

	gbuffer_data gbd = gbuffer_load_data( GLD_P(I.tc.xy/I.tc.w, I.hpos, ISAMPLE) );

#ifdef	GBUFFER_OPTIMIZATION
	//	Emulate virtual offset
	gbd.P += gbd.N*0.015f;
#endif	//	GBUFFER_OPTIMIZATION

	float4 _P = float4( gbd.P, gbd.mtl );
	float4  _N = float4( gbd.N, gbd.hemi );

	// ----- light-model
	float	m	= xmaterial;
# ifndef USE_R2_STATIC_SUN
			m 	= _P.w;
# endif
	float4	light	= plight_infinity ( m, _P, _N, Ldynamic_dir );

	// ----- shadow
  	float4 	P4 	= float4( _P.x, _P.y, _P.z, 1.f);
	float4 	PS	= mul( m_shadow, P4 );
	float 	s 	= sunmask( P4 );
	#if defined	(USE_SJITTER) || SUN_QUALITY==2 // Hight quality
	  		s 	*= shadow_high(PS); //shadowtest_sun( PS, float4(0,0,0,0) );
	#else
#ifdef SM_MINMAX
		#ifdef USE_SJITTER
	  		s 	*= shadow_dx10_1( PS, I.tcJ, I.hpos.xy );
		#else
			s *= shadow( PS );
		#endif
#else
			s *= shadow( PS );
#endif
	#endif

	// Far edge fading code
	float2 	tc_f	= (PS.xy/PS.w)-float2(0.5f,0.5f);
			// Fade only fron edges
			tc_f 	*= step( -dot( tc_f, view_shadow_proj.xy ), 0 );
			tc_f	= abs( tc_f );
	float 	border 	= 0.4f;
	float 	fac_x 	= 1.f-saturate( ( tc_f.x - border )/(0.5f-border));
	float 	fac_y 	= 1.f-saturate( ( tc_f.y - border )/(0.5f-border));
	
	s += ((1-s)*(1-fac_x*fac_y));
	//\ Far edge fading code

	return 		blend( Ldynamic_color * light * s/*float4( 1.f, 0.2f, 0.2f, 1.f)*/, I.tc );
}
#endif
