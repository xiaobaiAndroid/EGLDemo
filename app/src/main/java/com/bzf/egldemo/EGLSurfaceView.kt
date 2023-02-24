package com.bzf.egldemo

import android.content.Context
import android.util.AttributeSet
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView

/**
 *@author: baizf
 *@date: 2023/2/24
 */
class EGLSurfaceView: SurfaceView,SurfaceHolder.Callback {


    constructor(context: Context, attributeSet: AttributeSet?): this(context,attributeSet,0)
    constructor(context: Context): this(context,null)

    constructor(context: Context, attributeSet: AttributeSet?, defStyleAttr: Int): super(context,attributeSet,defStyleAttr){
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        nSurfaceCreated(holder.surface)
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        nSurfaceChanged(width,height)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        nSurfaceDestroyed()
    }

    private external fun nSurfaceCreated(surface: Surface)
    private external fun nSurfaceChanged(width: Int, height: Int)
    private external fun nSurfaceDestroyed()

    companion object {
        init {
            System.loadLibrary("eglsample")
        }
    }
}