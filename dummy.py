import numpy as np
import cv2
from matplotlib import pyplot as plt
from typing import *
import matplotlib.patches as patches
from matplotlib.transforms import Affine2D
from patternmatching.helper_funs import *

class ROI_:
    def __init__(self,LabVIEW_roi:dict,*args,**kwargs) -> None:
        self._global_rectangle = LabVIEW_roi['global rectangle']
        self._contour_type = LabVIEW_roi['contour type']
        self._points = LabVIEW_roi['points']
    
    @property
    def global_rectangle(self):
        return self._global_rectangle
        

class RectRoi(ROI_):
    def __init__(self, LabVIEW_roi: dict,*args,**kwargs) -> None:
        super().__init__(LabVIEW_roi,*args,**kwargs)

    def _transform_the_roi(self,h):
        a, b, c, d = self._points[:-1]
        self.__center = ((a+c)/2,(b+d)/2)
        size =  (abs(c-a),abs(d-b))
        angle = self._points[-1]/1000

        rotation_matrix = cv2.getRotationMatrix2D(self.__center, angle, scale=1)

        rect_points = np.array([
            [a, b],
            [c, b],
            [c, d],
            [a, d]
        ])
        transformed_coordinates = cv2.transform(np.array([rect_points]), rotation_matrix).astype(int)[0]

        r = transformed_coordinates.reshape(-1,1,2).astype('float32')

        r = cv2.perspectiveTransform(r,h)
        r = r.squeeze()
        
        vector1 = r[1] - r[0]
        vector2 = r[2] - r[1]

        angle1 = np.arctan2(vector1[1],vector1[0])
        angle2 = np.arctan2(vector2[1],vector2[0])

        rotationMat = cv2.getRotationMatrix2D(np.mean(r,axis=0),np.degrees(angle1),scale=1)
        transformed_coordinates =  cv2.transform(np.array([r]), rotationMat).astype(np.int32)[0]
        # print('transformed 0-deg rect',transformed_coordinates)
        minx,miny = np.min(transformed_coordinates[:,0]), np.min(transformed_coordinates[:,1])
        maxx,maxy = np.max(transformed_coordinates[:,0]), np.max(transformed_coordinates[:,1])

        self._points = [minx, miny, maxx, maxy, -np.degrees(angle1)*1000]

        return self._points


class AnnulusRoi(ROI_):
    def __init__(self, LabVIEW_roi: dict, *args, **kwargs) -> None:
        super().__init__(LabVIEW_roi, *args, **kwargs) 
        """
        Format
        -------
        [center x, center y, inner radius, 
         outer radius, start angle, end angle]
        """
        self._center = self._points[:2]
        self._inner_radius = self._points[2]
        self._outer_radius = self._points[3]
        self._starting_angle = self._points[-2]/1000 # theta 
        self._ending_angle = self._points[-1]/1000   # phi
        self.__angle = kwargs.get('angle',0)
        

    def _transform_the_roi(self,h):
        angle = self.__angle
        x,y = self._center
        # transformed_center = np.dot(h,np.array([[x,y,1]]).T).squeeze()[:2]
        transformed_center = cv2.perspectiveTransform(np.array([[x,y]],dtype='float32').reshape(-1,1,2),h)
        transformed_center = transformed_center .reshape(-1)
        self._starting_angle += (angle)
        self._ending_angle += (angle)

        return [transformed_center[0],transformed_center[1],self._inner_radius,self._outer_radius,self._starting_angle*1000,self._ending_angle*1000]


class PointRoi(ROI_):
    def __init__(self, LabVIEW_roi: dict, *args, **kwargs) -> None:
        super().__init__(LabVIEW_roi, *args, **kwargs)

    def _transform_the_roi(self,h):
        x,y = self._points
        transformed_center = cv2.perspectiveTransform(np.array([[x,y]],dtype='float32').reshape(-1,1,2),h)
        transformed_center = transformed_center .reshape(-1)
        # print(f' [{x}, {y}] inside the point ROI')
        # print(f' this is the transformed points : {transformed_center.squeeze()[:2]}')
        transformed_roi =  transformed_center.squeeze()[:2]
        self._global_rectangle = [transformed_roi[0],transformed_roi[1],transformed_roi[0]+1, transformed_roi[1]+1]
        return transformed_roi

    
