#ifndef __MATRIX_HEADER__
#define __MATRIX_HEADER__

//==========[ Forward References ]=============================================

template <class T> class Vec3;
template <class T> class Vec4;
template <class T> class Mat3;
template <class T> class Mat4;

#include "vec.h"

//==========[ Inline Method Definitions (Matrix) ]=============================

template <class T>
inline Mat3<T> operator -( const Mat3<T>& a );

template <class T>
inline Mat3<T> operator +( const Mat3<T>& a, const Mat3<T>& b );

template <class T>
inline Mat3<T> operator -( const Mat3<T>& a, const Mat3<T>& b);

template <class T>
inline Mat3<T> operator *( const Mat3<T>& a, const Mat3<T>& b );

template <class T>
inline Mat3<T> operator *( const Mat3<T>& a, const double d );

template <class T>
inline Mat3<T> operator *( const double d, const Mat3<T>& a );

template <class T>
inline Mat3<T> operator /( const Mat3<T>& a, const double d );

template <class T>
inline bool operator ==( const Mat3<T>& a, const Mat3<T>& b );

template <class T>
inline bool operator !=( const Mat3<T>& a, const Mat3<T>& b );

template <class T>
inline Mat4<T> operator -( const Mat4<T>& a );

template <class T>
inline Mat4<T> operator +( const Mat4<T>& a, const Mat4<T>& b );

template <class T>
inline Mat4<T> operator -( const Mat4<T>& a, const Mat4<T>& b );

template <class T>
inline Mat4<T> operator *( const Mat4<T>& a, const Mat4<T>& b );

template <class T>
inline Mat4<T> operator *( const Mat4<T>& a, const double d );

template <class T>
inline Mat4<T> operator *( const double d, const Mat4<T>& a );

template <class T>
inline Mat4<T> operator /( const Mat4<T>& a, const double d );

template <class T>
inline bool operator ==( const Mat4<T>& a, const Mat4<T>& b );

template <class T>
inline bool operator !=( const Mat4<T>& a, const Mat4<T>& b );

// These are handy functions

template <class T>
inline void makeDiagonal( Mat4<T>& m, T k );

template <class T>
inline void makeHScale( Mat4<T>& m, T sx, T sy, T sz );

template <class T>
inline void makeHScale( Mat4<T>& m, const Vec3<T> &v);

template <class T>
inline void makeHTrans( Mat4<T>& m, T tx, T ty, T tz );

template <class T>
inline void makeHTrans( Mat4<T>& m, const Vec3<T> &v);

template <class T>
inline void makeHRotX( Mat4<T>& m, T thetaX );

template <class T>
inline void makeHRotY( Mat4<T>& m, T thetaY );

template <class T>
inline void makeHRotZ( Mat4<T>& m, T thetaZ );

template <class T>
inline void makeHRot( Mat4<T>& m, T theta, Vec3<T>& axis);

//==========[ class Mat3 ]=====================================================

template <class T>
class Mat3 {

	//---[ Private Variable Declarations ]-----------------

		// matrix elements in row major order
	T		n[9];

public:
	
	//---[ Constructors ]----------------------------------

	Mat3()
		{ memset(n,0,9*sizeof(T)); n[0]=1; n[3]=1; n[6]=1; }
	Mat3( T n0, T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8 )
		{ n[0]=n0; n[1]=n1; n[2]=n2;
		  n[3]=n3; n[4]=n4; n[5]=n5;
		  n[6]=n6; n[7]=n7; n[8]=n8; }
	Mat3( const Mat3<T>& m )
		{ memcpy(n,m.n,9*sizeof(T)); }
	Mat3( const T m[3][3] )
		{ memcpy(n,m,9*sizeof(T)); }
	//Mat3( const T *m )
	//	{ memcpy(n,m,9*sizeof(T)); }


	//---[ Equal Operators ]-------------------------------

	Mat3<T>& operator =( const Mat3<T>& m )
		{ memcpy(n,m.n,9*sizeof(T)); return *this; }
	Mat3<T>& operator +=( const Mat3<T>& m )
		{ n[0]+=m.n[0]; n[1]+=m.n[1]; n[2]+=m.n[2]; n[3]+=m.n[3]; n[4]+=m.n[4]; n[5]+=m.n[5]; n[6]+=m.n[6]; n[7]+=m.n[7]; n[8]+=m.n[8]; return *this; }
	Mat3<T>& operator -=( const Mat3<T>& m )
		{ n[0]-=m.n[0]; n[1]-=m.n[1]; n[2]-=m.n[2]; n[3]-=m.n[3]; n[4]-=m.n[4]; n[5]-=m.n[5]; n[6]-=m.n[6]; n[7]-=m.n[7]; n[8]-=m.n[8]; return *this; }
	Mat3<T>& operator *=( const T d )
		{ n[0]*=d; n[1]*=d; n[2]*=d; n[3]*=d; n[4]*=d; n[5]*=d; n[6]*=d; n[7]*=d; n[8]*=d; return *this; }
	Mat3<T>& operator /=( const T d )
		{ n[0]/=d; n[1]/=d; n[2]/=d; n[3]/=d; n[4]/=d; n[5]/=d; n[6]/=d; n[7]/=d; n[8]/=d; return *this; }

	//---[ Access Operators ]------------------------------

	T* operator []( int i )
		{ return &n[i*3]; }
	const T* operator []( int i ) const
		{ return &n[i*3]; }

	//---[ Ordering Methods ]------------------------------

	Mat3<T> transpose() const { return Mat3<T>(n[0],n[3],n[6],n[1],n[4],n[7],n[2],n[5],n[8]) }
	double trace() const { return n[0]+n[4]+n[8]; }
	
	//---[ GL Matrix ]-------------------------------------

	void getGLMatrix( T* mat ) const
	{ mat[0]=n[0]; mat[1]=n[3]; mat[2]=n[6];
	  mat[3]=n[1]; mat[4]=n[4]; mat[5]=n[7];
	  mat[6]=n[2]; mat[7]=n[5]; mat[8]=n[8]; }

	//---[ Friend Methods ]--------------------------------

	friend Mat3<T> operator -<>( const Mat3<T>& a );
	friend Mat3<T> operator +<>( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator -<>( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator *<>( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator *<>( const Mat3<T>& a, const double d );
	friend Mat3<T> operator *<>( const double d, const Mat3<T>& a );
	friend Mat3<T> operator /<>( const Mat3<T>& a, const double d );
	friend Vec3<T> operator *<>( const Mat3<T>& a, const Vec3<T>& v );
	friend bool operator ==<>( const Mat3<T>& a, const Mat3<T>& b );
	friend bool operator !=<>( const Mat3<T>& a, const Mat3<T>& b );
};

typedef Mat3<int> Mat3i;
typedef Mat3<float> Mat3f;
typedef Mat3<double> Mat3d;

//==========[ class Mat4 ]=====================================================

template <class T>
class Mat4 {

	//---[ Private Variable Declarations ]-----------------

		// matrix elements in row-major order
	T		n[16];

public:

	bool isZero() { return n[0]==0&&n[1]==0&&n[2]==0&&n[3]==0&&n[4]==0&&n[5]==0&&n[6]==0&&n[7]==0&&n[8]==0&&n[9]==0&&n[10]==0&&n[11]==0&&n[12]==0&&n[13]==0&&n[14]==0&&n[15]==0; }
	
	//---[ Constructors ]----------------------------------

	Mat4()
		{ memset(n,0,16*sizeof(T)); n[0]=1;n[5]=1;n[10]=1;n[15]=1; }
	Mat4( T n0, T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8, T n9, T n10, T n11, T n12, T n13, T n14, T n15 )
		{ n[ 0]=n0 ; n[ 1]=n1 ; n[ 2]=n2 ; n[ 3]=n3 ;
		  n[ 4]=n4 ; n[ 5]=n5 ; n[ 6]=n6 ; n[ 7]=n7 ;
		  n[ 8]=n8 ; n[ 9]=n9 ; n[10]=n10; n[11]=n11;
		  n[12]=n12; n[13]=n13; n[14]=n14; n[15]=n15; }	  
	Mat4( const Mat4<T>& m )
		{ memcpy(n,m.n,16*sizeof(T)); }

	//---[ Equal Operators ]-------------------------------

	Mat4<T>& operator =( const Mat4<T>& m )
		{ memcpy(n,m.n,16*sizeof(T)); return *this; }
	Mat4<T>& operator +=( const Mat4<T>& m )
		{ n[ 0]+=m.n[ 0]; n[ 1]+=m.n[ 1]; n[ 2]+=m.n[ 2]; n[ 3]+=m.n[ 3];
		  n[ 4]+=m.n[ 4]; n[ 5]+=m.n[ 5]; n[ 6]+=m.n[ 6]; n[ 7]+=m.n[ 7];
		  n[ 8]+=m.n[ 8]; n[ 9]+=m.n[ 9]; n[10]+=m.n[10]; n[11]+=m.n[11];
		  n[12]+=m.n[12]; n[13]+=m.n[13]; n[14]+=m.n[14]; n[15]+=m.n[15]; 
		  return *this; }
	Mat4<T>& operator -=( const Mat4<T>& m )
		{ n[ 0]-=m.n[ 0]; n[ 1]-=m.n[ 1]; n[ 2]-=m.n[ 2]; n[ 3]-=m.n[ 3];
		  n[ 4]-=m.n[ 4]; n[ 5]-=m.n[ 5]; n[ 6]-=m.n[ 6]; n[ 7]-=m.n[ 7];
		  n[ 8]-=m.n[ 8]; n[ 9]-=m.n[ 9]; n[10]-=m.n[10]; n[11]-=m.n[11];
		  n[12]-=m.n[12]; n[13]-=m.n[13]; n[14]-=m.n[14]; n[15]-=m.n[15]; 
		  return *this; }
	Mat4<T>& operator *=( const T d )
		{ n[ 0]*=d; n[ 1]*=d; n[ 2]*=d; n[ 3]*=d;
		  n[ 4]*=d; n[ 5]*=d; n[ 6]*=d; n[ 7]*=d;
		  n[ 8]*=d; n[ 9]*=d; n[10]*=d; n[11]*=d;
		  n[12]*=d; n[13]*=d; n[14]*=d; n[15]*=d; 
		  return *this; }
	Mat4<T>& operator /=( const T d )
		{ n[ 0]/=d; n[ 1]/=d; n[ 2]/=d; n[ 3]/=d;
		  n[ 4]/=d; n[ 5]/=d; n[ 6]/=d; n[ 7]/=d;
		  n[ 8]/=d; n[ 9]/=d; n[10]/=d; n[11]/=d;
		  n[12]/=d; n[13]/=d; n[14]/=d; n[15]/=d; 
		  return *this; }

	//---[ Access Operators ]------------------------------

	T* operator []( int i )
		{ return &n[i*4]; }
	const T* operator []( int i ) const
		{ return &n[i*4]; }

	//---[ Ordering Methods ]------------------------------

	Mat4<T> transpose() const
		{ return Mat4<T>(n[ 0],n[ 4],n[ 8],n[12],
						 n[ 1],n[ 5],n[ 9],n[13],
						 n[ 2],n[ 6],n[10],n[14],
						 n[ 3],n[ 7],n[11],n[15]); }

	double trace() const { return n[0]+n[5]+n[10]+n[15]; }


	Mat4<T> inverse() const {
        // regular old gaussian elimination
		Mat4<T> invM;
		const Mat4<T> &m = *this;

		int i, j, k;
		double temp;
		double bigm[8][4];
		/*   Declare identity matrix   */
		
		invM[0][0] = 1; invM[0][1] = 0; invM[0][2] = 0;	invM[0][3] = 0;
		invM[1][0] = 0;	invM[1][1] = 1;	invM[1][2] = 0;	invM[1][3] = 0;
		invM[2][0] = 0;	invM[2][1] = 0;	invM[2][2] = 1;	invM[2][3] = 0;
		invM[3][0] = 0;	invM[3][1] = 0;	invM[3][2] = 0;	invM[3][3] = 1;
		
		for (i = 0; i < 4; i++) {
			for (j = 0;  j < 4;  j++) {
				bigm[i][j] = m[i][j];
				bigm[i+4][j] = invM[i][j];
			}
		}
		
		/*   Work across by columns   */
		for (i = 0;  i < 4;  i++) {
			for (j = i;  (bigm[i][j] == 0.0) && (j < 4);  j++)
				;
			if (j == 4) {
				fprintf (stderr, "error:  cannot do inverse matrix\n");
				exit (2);
			} 
			else if (i != j) {
				for (k = 0;  k < 8;  k++) {
					temp = bigm[k][i];   
					bigm[k][i] = bigm[k][j];   
					bigm[k][j] = temp;
				}
			}
			
			/*   Divide original row   */
			for (j = 7;  j >= i;  j--)
				bigm[j][i] /= bigm[i][i];
			
			/*   Subtract other rows   */
			
			for (j = 0;  j < 4;  j++)
				if (i != j)
					for (k = 7;  k >= i;  k--)
						bigm[k][j] -= bigm[k][i] * bigm[i][j];
		}
		
		for (i = 0;  i < 4;  i++)
		{
			for (j = 0;  j < 4;  j++)
				invM[i][j] = bigm[i+4][j];
		}

		return invM;

			
	}


	void swapRows(int a, int b) {
		T		temp;

		for( int i=0;i<4;i++ ) {
			temp = n[a*4+i];
			n[a*4+i] = n[b*4+i];
			n[b*4+i] = temp;
		}
	}
	
	//---[ GL Matrix ]-------------------------------------

	void getGLMatrix( T* mat ) const
	{ mat[ 0]=n[ 0]; mat[ 1]=n[ 4]; mat[ 2]=n[ 8]; mat[ 3]=n[12];
	  mat[ 4]=n[ 1]; mat[ 5]=n[ 5]; mat[ 6]=n[ 9]; mat[ 7]=n[13];
	  mat[ 8]=n[ 2]; mat[ 9]=n[ 6]; mat[10]=n[10]; mat[11]=n[14];
	  mat[12]=n[ 3]; mat[13]=n[ 7]; mat[14]=n[11]; mat[15]=n[15]; }

	//---[ Transformation Matrices ]-----------------------

	static Mat4<T> createRotation( T angle, float x, float y, float z );
	static Mat4<T> createTranslation( T x, T y, T z );
	static Mat4<T> createScale( T sx, T sy, T sz );
	static Mat4<T> createShear( T shx, T shy, T shz );
	
	//---[ Friend Methods ]--------------------------------

	friend Mat4<T> operator -<>( const Mat4<T>& a );
	friend Mat4<T> operator +<>( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator -<>( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator *<>( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator *<>( const Mat4<T>& a, const double d );
	friend Mat4<T> operator *<>( const double d, const Mat4<T>& a );
	friend Vec3<T> operator *<>( const Mat4<T>& a, const Vec3<T>& b );
	friend Vec4<T> operator *<>( const Mat4<T>& a, const Vec4<T>& b );
	friend Mat4<T> operator /<>( const Mat4<T>& a, const double d );
	friend bool operator ==<>( const Mat4<T>& a, const Mat4<T>& b );
	friend bool operator !=<>( const Mat4<T>& a, const Mat4<T>& b );
};

typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

//==========[ Inline Method Definitions (Matrix) ]=============================

template <class T>
inline Mat3<T> operator -( const Mat3<T>& a ) {
	return Mat3<T>( -a.n[0], -a.n[1], -a.n[2],
					-a.n[3], -a.n[4], -a.n[5],
					-a.n[6], -a.n[7], -a.n[8] );
}

template <class T>
inline Mat3<T> operator +( const Mat3<T>& a, const Mat3<T>& b ) {
	return Mat3<T>( a.n[0]+b.n[0], a.n[1]+b.n[1], a.n[2]+b.n[2],
					a.n[3]+b.n[3], a.n[4]+b.n[4], a.n[5]+b.n[5],
					a.n[6]+b.n[6], a.n[7]+b.n[7], a.n[8]+b.n[8],);
}

template <class T>
inline Mat3<T> operator -( const Mat3<T>& a, const Mat3<T>& b) {
	return Mat3<T>( a.n[0]-b.n[0], a.n[1]-b.n[1], a.n[2]-b.n[2],
					a.n[3]-b.n[3], a.n[4]-b.n[4], a.n[5]-b.n[5],
					a.n[6]-b.n[6], a.n[7]-b.n[7], a.n[8]-b.n[8],);
}

template <class T>
inline Mat3<T> operator *( const Mat3<T>& a, const Mat3<T>& b ) {
	return Mat3<T>( a.n[0]*b.n[0]+a.n[1]*b.n[3]+a.n[2]*b.n[6],
					a.n[0]*b.n[1]+a.n[1]*b.n[4]+a.n[2]*b.n[7],
					a.n[0]*b.n[2]+a.n[1]*b.n[5]+a.n[2]*b.n[8],
					a.n[3]*b.n[0]+a.n[4]*b.n[3]+a.n[5]*b.n[6],
					a.n[3]*b.n[1]+a.n[4]*b.n[4]+a.n[5]*b.n[7],
					a.n[3]*b.n[2]+a.n[4]*b.n[5]+a.n[5]*b.n[8],
					a.n[6]*b.n[0]+a.n[7]*b.n[3]+a.n[8]*b.n[6],
					a.n[6]*b.n[1]+a.n[7]*b.n[4]+a.n[8]*b.n[7],
					a.n[6]*b.n[2]+a.n[7]*b.n[5]+a.n[8]*b.n[8] );
}

template <class T>
inline Mat3<T> operator *( const Mat3<T>& a, const double d ) {
	return Mat3<T>( a.n[0]*d, a.n[1]*d, a.n[2]*d,
					a.n[3]*d, a.n[4]*d, a.n[5]*d,
					a.n[6]*d, a.n[7]*d, a.n[8]*d );
}

template <class T>
inline Mat3<T> operator *( const double d, const Mat3<T>& a ) {
	return Mat3<T>( a.n[0]*d, a.n[1]*d, a.n[2]*d,
					a.n[3]*d, a.n[4]*d, a.n[5]*d,
					a.n[6]*d, a.n[7]*d, a.n[8]*d );
}

template <class T>
inline Mat3<T> operator /( const Mat3<T>& a, const double d ) {
	return Mat3<T>( a.n[0]/d, a.n[1]/d, a.n[2]/d,
					a.n[3]/d, a.n[4]/d, a.n[5]/d,
					a.n[6]/d, a.n[7]/d, a.n[8]/d );
}

template <class T>
inline bool operator ==( const Mat3<T>& a, const Mat3<T>& b ) {
	return !memcmp( a.n, b.n, 9*sizeof(T) );
}

template <class T>
inline bool operator !=( const Mat3<T>& a, const Mat3<T>& b ) {
	return memcmp( a.n, b.n, 9*sizeof(T) );
}

template <class T>
inline Mat4<T> operator -( const Mat4<T>& a ) {
	return Mat4<T>( -a.n[ 0], -a.n[ 1], -a.n[ 2], -a.n[ 3],
					-a.n[ 4], -a.n[ 5], -a.n[ 6], -a.n[ 7],
					-a.n[ 8], -a.n[ 9], -a.n[10], -a.n[11],
					-a.n[12], -a.n[13], -a.n[14], -a.n[15] );
}

template <class T>
inline Mat4<T> operator +( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]+b.n[ 0], a.n[ 1]+b.n[ 1], a.n[ 2]+b.n[ 2], a.n[ 3]+b.n[ 3],
					a.n[ 4]+b.n[ 4], a.n[ 5]+b.n[ 5], a.n[ 6]+b.n[ 6], a.n[ 7]+b.n[ 7],
					a.n[ 8]+b.n[ 8], a.n[ 9]+b.n[ 9], a.n[10]+b.n[10], a.n[11]+b.n[11],
					a.n[12]+b.n[12], a.n[13]+b.n[13], a.n[14]+b.n[14], a.n[15]+b.n[15] );
}

template <class T>
inline Mat4<T> operator -( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]-b.n[ 0], a.n[ 1]-b.n[ 1], a.n[ 2]-b.n[ 2], a.n[ 3]-b.n[ 3],
					a.n[ 4]-b.n[ 4], a.n[ 5]-b.n[ 5], a.n[ 6]-b.n[ 6], a.n[ 7]-b.n[ 7],
					a.n[ 8]-b.n[ 8], a.n[ 9]-b.n[ 9], a.n[10]-b.n[10], a.n[11]-b.n[11],
					a.n[12]-b.n[12], a.n[13]-b.n[13], a.n[14]-b.n[14], a.n[15]-b.n[15] );
}

template <class T>
inline Mat4<T> operator *( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]*b.n[ 0]+a.n[ 1]*b.n[ 4]+a.n[ 2]*b.n[ 8]+a.n[ 3]*b.n[12],
					a.n[ 0]*b.n[ 1]+a.n[ 1]*b.n[ 5]+a.n[ 2]*b.n[ 9]+a.n[ 3]*b.n[13],
					a.n[ 0]*b.n[ 2]+a.n[ 1]*b.n[ 6]+a.n[ 2]*b.n[10]+a.n[ 3]*b.n[14],
					a.n[ 0]*b.n[ 3]+a.n[ 1]*b.n[ 7]+a.n[ 2]*b.n[11]+a.n[ 3]*b.n[15],
					a.n[ 4]*b.n[ 0]+a.n[ 5]*b.n[ 4]+a.n[ 6]*b.n[ 8]+a.n[ 7]*b.n[12],
					a.n[ 4]*b.n[ 1]+a.n[ 5]*b.n[ 5]+a.n[ 6]*b.n[ 9]+a.n[ 7]*b.n[13],
					a.n[ 4]*b.n[ 2]+a.n[ 5]*b.n[ 6]+a.n[ 6]*b.n[10]+a.n[ 7]*b.n[14],
					a.n[ 4]*b.n[ 3]+a.n[ 5]*b.n[ 7]+a.n[ 6]*b.n[11]+a.n[ 7]*b.n[15],
					a.n[ 8]*b.n[ 0]+a.n[ 9]*b.n[ 4]+a.n[10]*b.n[ 8]+a.n[11]*b.n[12],
					a.n[ 8]*b.n[ 1]+a.n[ 9]*b.n[ 5]+a.n[10]*b.n[ 9]+a.n[11]*b.n[13],
					a.n[ 8]*b.n[ 2]+a.n[ 9]*b.n[ 6]+a.n[10]*b.n[10]+a.n[11]*b.n[14],
					a.n[ 8]*b.n[ 3]+a.n[ 9]*b.n[ 7]+a.n[10]*b.n[11]+a.n[11]*b.n[15],
					a.n[12]*b.n[ 0]+a.n[13]*b.n[ 4]+a.n[14]*b.n[ 8]+a.n[15]*b.n[12],
					a.n[12]*b.n[ 1]+a.n[13]*b.n[ 5]+a.n[14]*b.n[ 9]+a.n[15]*b.n[13],
					a.n[12]*b.n[ 2]+a.n[13]*b.n[ 6]+a.n[14]*b.n[10]+a.n[15]*b.n[14],
					a.n[12]*b.n[ 3]+a.n[13]*b.n[ 7]+a.n[14]*b.n[11]+a.n[15]*b.n[15] );
}

template <class T>
inline Mat4<T> operator *( const Mat4<T>& a, const double d ) {
	return Mat4<T>( a.n[ 0]*d, a.n[ 1]*d, a.n[ 2]*d, a.n[ 3]*d,
					a.n[ 4]*d, a.n[ 5]*d, a.n[ 6]*d, a.n[ 7]*d,
					a.n[ 8]*d, a.n[ 9]*d, a.n[10]*d, a.n[11]*d,
					a.n[12]*d, a.n[13]*d, a.n[14]*d, a.n[15]*d );
}

template <class T>
inline Mat4<T> operator *( const double d, const Mat4<T>& a ) {
	return Mat4<T>( a.n[ 0]*d, a.n[ 1]*d, a.n[ 2]*d, a.n[ 3]*d,
					a.n[ 4]*d, a.n[ 5]*d, a.n[ 6]*d, a.n[ 7]*d,
					a.n[ 8]*d, a.n[ 9]*d, a.n[10]*d, a.n[11]*d,
					a.n[12]*d, a.n[13]*d, a.n[14]*d, a.n[15]*d );
}

template <class T>
inline Mat4<T> operator /( const Mat4<T>& a, const double d ) {
	return Mat4<T>( a.n[ 0]/d, a.n[ 1]/d, a.n[ 2]/d, a.n[ 3]/d,
					a.n[ 4]/d, a.n[ 5]/d, a.n[ 6]/d, a.n[ 7]/d,
					a.n[ 8]/d, a.n[ 9]/d, a.n[10]/d, a.n[11]/d,
					a.n[12]/d, a.n[13]/d, a.n[14]/d, a.n[15]/d );
}

template <class T>
inline bool operator ==( const Mat4<T>& a, const Mat4<T>& b ) {
	return !memcmp(a.n,b.n,16*sizeof(T));
}

template <class T>
inline bool operator !=( const Mat4<T>& a, const Mat4<T>& b ) {
	return memcmp(a.n,b.n,16*sizeof(T));
}

// These are handy functions

template <class T>
inline void makeDiagonal( Mat4<T>& m, T k ) {
	m[0][0] =   k; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = 0.0;
	m[1][0] = 0.0; m[1][1] =   k; m[1][2] = 0.0; m[1][3] = 0.0;
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] =   k; m[2][3] = 0.0;
	m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] =   k;
}

template <class T>
inline void makeHScale( Mat4<T>& m, T sx, T sy, T sz ) {
	m[0][0] =  sx; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = 0.0;
	m[1][0] = 0.0; m[1][1] =  sy; m[1][2] = 0.0; m[1][3] = 0.0;
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] =  sz; m[2][3] = 0.0;
	m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHScale( Mat4<T>& m, const Vec3<T> &v) {
	makeHScale(m, v[0], v[1], v[2]);
}

template <class T>
inline void makeHTrans( Mat4<T>& m, T tx, T ty, T tz ) {
	m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] =  tx;
	m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] =  ty;
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] =  tz;
	m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHTrans( Mat4<T>& m, const Vec3<T> &v) {
	makeHTrans(m, v[0], v[1], v[2]);
}

template <class T>
inline void makeHRotX( Mat4<T>& m, T thetaX ) {
	T cosT = (T)cos(thetaX);
	T sinT = (T)sin(thetaX);

	m[0][0] = 1.0; m[0][1] =  0.0; m[0][2] =   0.0; m[0][3] = 0.0;
	m[1][0] = 0.0; m[1][1] = cosT; m[1][2] = -sinT; m[1][3] = 0.0;
	m[2][0] = 0.0; m[2][1] = sinT; m[2][2] =  cosT; m[2][3] = 0.0;
	m[3][0] = 0.0; m[3][1] =  0.0; m[3][2] =   0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHRotY( Mat4<T>& m, T thetaY ) {
	T cosT = (T)cos(thetaY);
	T sinT = (T)sin(thetaY);

	m[0][0] =  cosT; m[0][1] = 0.0; m[0][2] = sinT; m[0][3] = 0.0;
	m[1][0] =   0.0; m[1][1] = 1.0; m[1][2] =  0.0; m[1][3] = 0.0;
	m[2][0] = -sinT; m[2][1] = 0.0; m[2][2] = cosT; m[2][3] = 0.0;
	m[3][0] =   0.0; m[3][1] = 0.0; m[3][2] =  0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHRotZ( Mat4<T>& m, T thetaZ ) {
	T cosT = (T)cos(thetaZ);
	T sinT = (T)sin(thetaZ);

	m[0][0] = cosT; m[0][1] = -sinT; m[0][2] = 0.0; m[0][3] = 0.0;
	m[1][0] = sinT; m[1][1] =  cosT; m[1][2] = 0.0; m[1][3] = 0.0;
	m[2][0] =  0.0; m[2][1] =   0.0; m[2][2] = 1.0; m[2][3] = 0.0;
	m[3][0] =  0.0; m[3][1] =   0.0; m[3][2] = 0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHRot( Mat4<T>& m, T theta, Vec3<T>& axis)
{
	Mat4d S, U, I;

	axis /= axis.length();

	const double &x = axis[0];
	const double &y = axis[1];
	const double &z = axis[2];

	S[0][0] = 0; S[0][1] = -z; S[0][2] = y;  S[0][3] = 0;
	S[1][0] = z; S[1][1] =  0; S[1][2] = -x; S[1][3] = 0;
	S[2][0] = -y; S[2][1] = x; S[2][2] = 0; S[2][3] = 0;
	S[3][0] = 0; S[3][1] = 0; S[3][2] = 0;   S[3][3] = 0;

	U[0][0] = x*x; U[0][1] = x*y; U[0][2] = x*z; U[0][3] = 0;
	U[1][0] = x*y; U[1][1] = y*y; U[1][2] = y*z; U[1][3] = 0;
	U[2][0] = x*z; U[2][1] = y*z; U[2][2] = z*z; U[2][3] = 0;
	U[3][0] = 0;   U[2][1] = 0;   U[3][2] = 0;   U[3][3] = 0;

	m = U + cos(theta)*(I-U) + sin(theta)*S;
	m[3][3] = 1;
}

template <class T>
inline void makeHRot( Mat4<T>& m, T theta, T x, T y, T z)
{
    makeHRot(m, theta, Vec3<T>(x,y,z));
}

#endif