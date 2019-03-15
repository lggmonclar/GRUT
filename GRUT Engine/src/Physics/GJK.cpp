#include "grutpch.h"
#include "Scene/GameObjects/GameObject.h"
#include "GJK.h"

namespace GRUT {
  bool GJK(const ObjectHandle<Collider>& p_a, const ObjectHandle<Collider>& p_b) {
    Vector<3> direction(1.0f, 1.0f, 0.0f);

    short pointCount = 0;
    Vector<3> simplexPoints[4];

    //Init simplex
    simplexPoints[pointCount++] = p_a->Support(direction) - p_b->Support(-direction);
    direction = -simplexPoints[0];

    int i = 0;
    while (i < MAX_ITERATIONS) {
      Vector<3> supportA = p_a->Support(direction);
      Vector<3> supportB = p_b->Support(-direction);

      Vector<3> furthestVertex = supportA - supportB;

      if (furthestVertex.Dot(direction) < 0) {
        //No intersection;
        return false;
      }

      simplexPoints[pointCount++] = furthestVertex;

      if (CheckIntersection(simplexPoints, pointCount, direction))
        return true;

      i++;
    }

    return false;
  }

  bool CheckIntersection(Vector<3> p_simplexPoints[4], short & p_pointCount, Vector<3>& p_direction) {
    if (p_pointCount == 2) {
      auto AB = p_simplexPoints[0] - p_simplexPoints[1];
      auto BO = -p_simplexPoints[1];

      p_direction = AB.Cross(BO).Cross(AB);
    }
    else if (p_pointCount == 3) {
      auto A = p_simplexPoints[0];
      auto B = p_simplexPoints[1];
      auto C = p_simplexPoints[2];

      auto CO = -C;

      auto CB = B - C;
      auto CA = A - C;
      auto CBA = CB.Cross(CA);

      if (IsSameDirection(CBA.Cross(CA), CO)) {
        if (IsSameDirection(CA, CO)) {
          p_simplexPoints[0] = C;
          p_simplexPoints[1] = A;

          p_direction = CA.Cross(CO).Cross(CA);
          p_pointCount = 2;
        }
        else if (IsSameDirection(CB, CO)) {
          p_simplexPoints[0] = B;
          p_simplexPoints[1] = C;

          p_direction = CB.Cross(CO).Cross(CB);
          p_pointCount = 2;
        }
        else {
          p_simplexPoints[0] = C;

          p_direction = CO;
          p_pointCount = 1;
        }
      }
      else {
        if (IsSameDirection(CB.Cross(CBA), CO)) {
          if (IsSameDirection(CB, CO)) {
            p_simplexPoints[0] = B;
            p_simplexPoints[1] = C;

            p_direction = CB.Cross(CO).Cross(CB);
            p_pointCount = 2;
          }
          else {
            p_simplexPoints[0] = C;

            p_direction = CO;
            p_pointCount = 1;
          }
        }
        else if (IsSameDirection(CBA, CO)) {
          p_simplexPoints[0] = B;
          p_simplexPoints[1] = A;
          p_simplexPoints[2] = C;

          p_direction = CBA;
        }
        else {
          p_direction = -CBA;
        }
      }
    }
    else if (p_pointCount == 4) {
      auto A = p_simplexPoints[0];
      auto B = p_simplexPoints[1];
      auto C = p_simplexPoints[2];
      auto D = p_simplexPoints[3];

      auto DO = -D;
      auto DC = C - D;
      auto DB = B - D;
      auto DA = A - D;
      auto DBC = DB.Cross(DC);
      auto DAB = DA.Cross(DB);
      auto DCA = DC.Cross(DA);

      if (IsSameDirection(DBC, DO)) {
        p_simplexPoints[0] = D;
        p_simplexPoints[1] = B;
        p_simplexPoints[2] = C;

        p_direction = DBC;
        p_pointCount = 3;
      }
      else if (IsSameDirection(DAB, DO)) {
        p_simplexPoints[0] = D;
        p_simplexPoints[1] = A;
        p_simplexPoints[2] = B;

        p_direction = DAB;
        p_pointCount = 3;
      }
      else if (IsSameDirection(DCA, DO)) {
        p_simplexPoints[0] = D;
        p_simplexPoints[1] = C;
        p_simplexPoints[2] = A;

        p_direction = DCA;
        p_pointCount = 3;
      }
      else {
        // Origin is contained
        return true;
      }
    }

    return false;
  }
}
