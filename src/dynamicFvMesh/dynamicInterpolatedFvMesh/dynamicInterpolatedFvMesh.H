/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::dynamicInterpolatedFvMesh

Description
    Interpolates pre-specified motion specified as a set of pointVectorFields.

    The motion can be provided either as a set of displacement or position
    fields and the entry \c displacement specified accordingly.

Usage
    Example:
    \verbatim
    dynamicFvMesh   dynamicInterpolatedFvMesh;

    displacementLaplacianCoeffs
    {
        field               wantedDisplacement;
        displacement        yes;
        interpolationScheme linear;
    }
    \endverbatim

    This will scan the case for \c wantedDisplacement \c pointVectorFields in
    the time directories and interpolate those in time (using \c linear
    interpolation) to obtain the current displacement.  The advantage of
    specifying displacement in this way is that it automatically works in
    parallel using \c decomposePar to decompose the set of \c pointVectorFields
    provided.

SourceFiles
    dynamicInterpolatedFvMesh.C

\*---------------------------------------------------------------------------*/

#ifndef dynamicInterpolatedFvMesh_H
#define dynamicInterpolatedFvMesh_H

#include "dynamicFvMesh.H"
#include "dynamicMeshPointInterpolator.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                    Class dynamicInterpolatedFvMesh Declaration
\*---------------------------------------------------------------------------*/

class dynamicInterpolatedFvMesh
:
    public dynamicFvMesh
{
    // Private data

        dictionary dynamicMeshCoeffs_;

        dynamicMeshPointInterpolator pointInterpolator_;

        const Switch displacement_;

        //- Starting points
        autoPtr<pointIOField> points0_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        dynamicInterpolatedFvMesh(const dynamicInterpolatedFvMesh&);

        //- Disallow default bitwise assignment
        void operator=(const dynamicInterpolatedFvMesh&);


public:

    //- Runtime type information
    TypeName("dynamicInterpolatedFvMesh");


    // Constructors

        //- Construct from IOobject
        dynamicInterpolatedFvMesh(const IOobject& io);


    //- Destructor
    ~dynamicInterpolatedFvMesh();


    // Member Functions

        //- Update the mesh for both mesh motion and topology change
        virtual bool update();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
