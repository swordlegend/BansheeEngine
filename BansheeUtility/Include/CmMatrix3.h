#pragma once

#include "CmPrerequisitesUtil.h"
#include "CmVector3.h"

namespace BansheeEngine
{
    /**
     * @brief	Class representing a 3x3 matrix.
     */
    class BS_UTILITY_EXPORT Matrix3
    {
	private:
		struct EulerAngleOrderData
		{
			int a, b, c;
			float sign;
		};

    public:
		Matrix3() {}

        Matrix3(const Matrix3& mat)
		{
			memcpy(m, mat.m, 9*sizeof(float));
		}

        Matrix3(float m00, float m01, float m02,
                float m10, float m11, float m12,
                float m20, float m21, float m22)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		}

		/**
         * @brief	Construct a matrix from a quaternion.
         */
        explicit Matrix3(const Quaternion& quad)
        {
            fromQuaternion(quad);
        }

		/**
         * @brief	Construct a matrix that performs rotation and scale.
         */
        explicit Matrix3(const Quaternion& quad, const Vector3 scale)
        {
            fromQuaternion(quad);
			
			for (int row = 0; row < 3; row++)
			{
				for (int col = 0; col < 3; col++)
					m[row][col] = scale[row]*m[row][col];
			}
        }

		/**
         * @brief	Construct a matrix from an angle/axis pair.
         */
        explicit Matrix3(const Vector3& axis, const Radian& angle)
        {
            fromAxisAngle(axis, angle);
        }

        /**
         * @brief	Construct a matrix from 3 orthonormal local axes.
         */
        explicit Matrix3(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
        {
            fromAxes(xaxis, yaxis, zaxis);
        }

        /**
         * @brief	Construct a matrix from euler angles, XYZ ordering.
         * 			
		 * @see		Matrix3::fromEulerAngles
         */
		explicit Matrix3(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle)
		{
			fromEulerAngles(xAngle, yAngle, zAngle);
		}

        /**
         * @brief	Construct a matrix from euler angles, custom ordering.
         * 			
		 * @see		Matrix3::fromEulerAngles
         */
		explicit Matrix3(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle, EulerAngleOrder order)
		{
			fromEulerAngles(xAngle, yAngle, zAngle, order);
		}

		/**
		 * @brief	Swaps the contents of this matrix with another.
		 */
		void swap(Matrix3& other)
		{
			std::swap(m[0][0], other.m[0][0]);
			std::swap(m[0][1], other.m[0][1]);
			std::swap(m[0][2], other.m[0][2]);
			std::swap(m[1][0], other.m[1][0]);
			std::swap(m[1][1], other.m[1][1]);
			std::swap(m[1][2], other.m[1][2]);
			std::swap(m[2][0], other.m[2][0]);
			std::swap(m[2][1], other.m[2][1]);
			std::swap(m[2][2], other.m[2][2]);
		}

        /**
         * @brief	Returns a row of the matrix.
         */
        inline float* operator[] (UINT32 row) const
		{
			assert(row < 3);

			return (float*)m[row];
		}

        Vector3 getColumn(UINT32 col) const;
        void setColumn(UINT32 col, const Vector3& vec);

        Matrix3& operator= (const Matrix3& rhs)
		{
			memcpy(m, rhs.m, 9*sizeof(float));
			return *this;
		}
        bool operator== (const Matrix3& rhs) const;
        bool operator!= (const Matrix3& rhs) const;

        Matrix3 operator+ (const Matrix3& rhs) const;
        Matrix3 operator- (const Matrix3& rhs) const;
        Matrix3 operator* (const Matrix3& rhs) const;
        Matrix3 operator- () const;
		Matrix3 operator* (float rhs) const;

		friend Matrix3 operator* (float lhs, const Matrix3& rhs);

		/**
		 * @brief	Transforms the given vector by this matrix and returns
		 * 			the newly transformed vector.
		 */
		Vector3 transform(const Vector3& vec) const;

        /**
         * @brief	Returns a transpose of the matrix (switched columns and rows).
         */
        Matrix3 transpose () const;

        /**
         * @brief	Calculates an inverse of the matrix if it exists.
         *
         * @param [out]	mat		Resulting matrix inverse.
         * @param	fTolerance 	(optional) Tolerance to use when checking
         * 						if determinant is zero (or near zero in this case).
         * 						Zero determinant means inverse doesn't exist.
         *
         * @return	True if inverse exists, false otherwise.
         */
        bool inverse(Matrix3& mat, float fTolerance = 1e-06f) const;

        /**
         * @brief	Calculates an inverse of the matrix if it exists.
         *
		 * @param	fTolerance 	(optional) Tolerance to use when checking
		 * 						if determinant is zero (or near zero in this case).
		 * 						Zero determinant means inverse doesn't exist.
         *
         * @return	Resulting matrix inverse if it exists, otherwise a zero matrix.
         */
        Matrix3 inverse(float fTolerance = 1e-06f) const;

        /**
         * @brief	Calculates the matrix determinant.
         */
        float determinant() const;

        /**
         * @brief	Decomposes the matrix into various useful values.
         *
         * @param [out]	matL	Unitary matrix. Columns form orthonormal bases. If your matrix is affine and
         * 						doesn't use non-uniform scaling this matrix will be a conjugate transpose of the rotation part of the matrix.
         * @param [out]	matS	Singular values of the matrix. If your matrix is affine these will be scaling factors of the matrix.
		 * @param [out]	matR	Unitary matrix. Columns form orthonormal bases. If your matrix is affine and
		 * 						doesn't use non-uniform scaling this matrix will be the rotation part of the matrix.
         */
        void singularValueDecomposition(Matrix3& matL, Vector3& matS, Matrix3& matR) const;

        /**
         * @brief	Decomposes the matrix into various useful values.
         *
         * @param [out]	matQ	Columns form orthonormal bases. If your matrix is affine and
         * 						doesn't use non-uniform scaling this matrix will be the rotation part of the matrix.
         * @param [out]	vecD	If your matrix is affine these will be scaling factors of the matrix.
		 * @param [out]	vecU	If your matrix is affine these will be shear factors of the matrix.
         */
		void QDUDecomposition(Matrix3& matQ, Vector3& vecD, Vector3& vecU) const;

        /**
         * @brief	Gram-Schmidt orthonormalization (applied to columns of rotation matrix)
         */
        void orthonormalize();

        /**
         * @brief	Converts an orthonormal matrix to axis angle representation.
         *
         * @note	Matrix must be orthonormal.
         */
        void toAxisAngle(Vector3& axis, Radian& angle) const;

        /**
         * @brief	Creates a rotation matrix from an axis angle representation.
         */
        void fromAxisAngle(const Vector3& axis, const Radian& angle);

        /**
         * @brief	Converts an orthonormal matrix to quaternion representation.
         *
         * @note	Matrix must be orthonormal.
         */
        void toQuaternion(Quaternion& quat) const;

        /**
         * @brief	Creates a rotation matrix from a quaternion representation.
         */
        void fromQuaternion(const Quaternion& quat);

        /**
         * @brief	Creates a matrix from a three axes.
         */
		void fromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

        /**
         * @brief	Extracts Pitch/Yaw/Roll rotations from this matrix.
         *
         * @param [in,out]	xAngle	Rotation about x axis. (AKA Pitch)
         * @param [in,out]	yAngle  Rotation about y axis. (AKA Yaw)
         * @param [in,out]	zAngle 	Rotation about z axis. (AKA Roll)
         *
         * @return	True if unique solution was found, false otherwise.
         * 			
		 * @note	Matrix must be orthonormal.
		 * 			
		 * 			Since different values will be returned depending in which order are the rotations applied, this method assumes
		 * 			they are applied in XYZ order. If you need a specific order, use the overloaded "toEulerAngles" method instead.
         */
        bool toEulerAngles(Radian& xAngle, Radian& yAngle, Radian& zAngle) const;

		/**
		 * @brief	Extracts Pitch/Yaw/Roll rotations from this matrix.
		 *
		 * @param	xAngle	Rotation about x axis. (AKA Pitch)
		 * @param	yAngle	Rotation about y axis. (AKA Yaw)
		 * @param	zAngle	Rotation about z axis. (AKA Roll)
		 * @param	order 	The order in which rotations will be extracted. 
		 * 					Different values can be retrieved depending on the order.
		 *
		 * @return	True if unique solution was found, false otherwise.
		 * 			
		 * @note	Matrix must be orthonormal.
		 */
		bool toEulerAngles(Radian& xAngle, Radian& yAngle, Radian& zAngle, EulerAngleOrder order) const;

        /**
         * @brief	Creates a rotation matrix from the provided Pitch/Yaw/Roll angles.
         *
		 * @param	xAngle	Rotation about x axis. (AKA Pitch)
		 * @param	yAngle	Rotation about y axis. (AKA Yaw)
		 * @param	zAngle	Rotation about z axis. (AKA Roll)
         *
         * @note	Matrix must be orthonormal.
		 * 			Since different values will be produced depending in which order are the rotations applied, this method assumes
		 * 			they are applied in XYZ order. If you need a specific order, use the overloaded "fromEulerAngles" method instead.
         */
        void fromEulerAngles(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle);

        /**
         * @brief	Creates a rotation matrix from the provided Pitch/Yaw/Roll angles.
         *
		 * @param	xAngle	Rotation about x axis. (AKA Pitch)
		 * @param	yAngle	Rotation about y axis. (AKA Yaw)
		 * @param	zAngle	Rotation about z axis. (AKA Roll)
		 * @param	order 	The order in which rotations will be extracted.
		 * 					Different values can be retrieved depending on the order.
         *
         * @note	Matrix must be orthonormal.
         */
        void fromEulerAngles(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle, EulerAngleOrder order);

        /**
         * @brief	Eigensolver, matrix must be symmetric.
         */
        void eigenSolveSymmetric(float eigenValues[3], Vector3 eigenVectors[3]) const;

        static const float EPSILON;
        static const Matrix3 ZERO;
        static const Matrix3 IDENTITY;

    protected:
		friend class Matrix4;

        // Support for eigensolver
        void tridiagonal (float diag[3], float subDiag[3]);
        bool QLAlgorithm (float diag[3], float subDiag[3]);

        // Support for singular value decomposition
        static const float SVD_EPSILON;
        static const unsigned int SVD_MAX_ITERS;
        static void bidiagonalize (Matrix3& matA, Matrix3& matL, Matrix3& matR);
        static void golubKahanStep (Matrix3& matA, Matrix3& matL, Matrix3& matR);

		// Euler angle conversions
		static const EulerAngleOrderData EA_LOOKUP[6];

        float m[3][3];
    };

	BS_ALLOW_MEMCPY_SERIALIZATION(Matrix3);
}